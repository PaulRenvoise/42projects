/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:24:27 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <unistd.h>
#include <sys/stat.h>

static void			builtin_cd_init_dest(t_env *e, char **dest)
{
	if (e->av[1] == NULL)
	{
		*dest = ft_strdup(e->home);
		e->av[3] = NULL;
	}
	else if (ft_strcmp(e->av[1], "-") == 0)
	{
		ft_putendl_fd(e->pwd_old, 0);
		*dest = ft_strdup(e->pwd_old);
	}
	else
		*dest = ft_strdup(e->av[1]);
}

static int			builtin_cd_error(char *dest)
{
	struct stat		sb;

	if (stat(dest, &sb) == -1)
	{
		ft_printf_fd("cd: no such file or directory: %s\n", 2, dest);
		return (1);
	}
	else if (S_ISREG(sb.st_mode))
	{
		ft_printf_fd("cd: not a directory: %s\n", 2, dest);
		return (1);
	}
	return (0);
}

int					builtin_cd(t_env *e, int fd)
{
	char			*buffer;
	char			*dest;

	buffer = NULL;
	e->av[3] = NULL;
	e->av[0] = ft_strdup("cd");
	builtin_cd_init_dest(e, &dest);
	if (builtin_cd_error(dest))
		return (1);
	e->av[1] = ft_strdup("OLDPWD");
	e->av[2] = getcwd(buffer, ft_strlen(e->pwd) + 15);
	e->pwd_old = ft_strdup(e->av[2]);
	builtin_setenv(e, fd);
	if (chdir(dest) == -1)
	{
		ft_printf_fd("cd: permission denied: %s\n", 2, dest);
		return (0);
	}
	e->av[1] = ft_strdup("PWD");
	e->av[2] = getcwd(buffer, ft_strlen(e->pwd) + ft_strlen(dest) + 16);
	builtin_setenv(e, fd);
	e->pwd = ft_strdup(e->av[2]);
	return (1);
}
