/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin_or_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:26:15 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

static char		*concat_path_name(char *str, char *path)
{
	char		*s;
	char		*tmp;

	if (!(tmp = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(str) + 2))))
		print_err("Malloc()", MALLOC);
	tmp = ft_strcpy(tmp, path);
	s = ft_strcat(tmp, "/");
	s = ft_strcat(s, str);
	return (s);
}

static int		check_access(char *path, t_env *e, t_fd *fd)
{
	struct stat	sb;

	if (stat(path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode))
			return (-1);
		if (access(path, X_OK) == 0)
		{
			execute_cmd(path, e, fd);
			return (1);
		}
		return (-1);
	}
	return (0);
}

static int		check_cmd_bs(t_env *e, t_fd *fd)
{
	if (check_access(e->av[0], e, fd) == 1)
		return (1);
	else if (check_access(e->av[0], e, fd) == -1)
	{
		ft_printf_fd("42sh: permission denied: %s\n", 2, e->av[0]);
		return (-1);
	}
	else if (check_access(e->av[0], e, fd) == 0)
	{
		ft_printf_fd("42sh: no such file or directory: %s\n", 2, e->av[0]);
		return (-1);
	}
	return (0);
}

int				check_cmd(t_env *e, t_fd *fd)
{
	char		*path;
	int			i;

	i = 0;
	path = NULL;
	while (e->paths && e->paths[i])
	{
		if (ft_strchr(e->av[0], '/'))
			return (check_cmd_bs(e, fd));
		path = concat_path_name(e->av[0], e->paths[i]);
		if (check_access(path, e, fd) == 1)
			return (1);
		else if (check_access(path, e, fd) == -1)
		{
			ft_printf_fd("42sh: permission denied: %s\n", 2, e->av[0]);
			return (0);
		}
		free(path);
		i++;
	}
	return (0);
}

int				check_builtin(t_env *e, int fd)
{
	int			i;

	i = 0;
	while (i < NB_BUILT_IN)
	{
		if (ft_strcmp(e->builtin[i].name, e->av[0]) == 0)
		{
			e->builtin[i].f(e, fd);
			return (1);
		}
		i++;
	}
	return (0);
}
