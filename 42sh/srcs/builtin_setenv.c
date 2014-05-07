/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:25:35 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:14:51 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <string.h>
#include <stdlib.h>

static int			builtin_setenv_error(t_env *e, int fd)
{
	if (e->av[1] == NULL)
	{
		builtin_env(e, fd);
		return (1);
	}
	else if (e->av[3] != NULL)
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return (1);
	}
	return (0);
}

int					builtin_setenv(t_env *e, int fd)
{
	size_t			i;

	if (!(i = 0) && builtin_setenv_error(e, fd))
		return (0);
	while (e->envp[i])
	{
		if (ft_strnstr(e->envp[i], e->av[1], ft_strlen(e->av[1]))
				&& ((e->envp[i])[ft_strlen(e->av[1])]) == '=')
		{
			e->envp[i] = ft_strjoin(e->av[1], "=");
			if (e->av[2] != NULL)
				e->envp[i] = ft_strjoin(e->envp[i], e->av[2]);
			init_env(e);
			return (1);
		}
		i++;
	}
	if (!(e->envp = (char **)ft_realloc(e->envp, sizeof(char *) * (i + 1))))
		print_err("Realloc()", MALLOC);
	e->envp[i] = ft_strjoin(ft_strdup(e->av[1]), "=");
	if (e->av[2] != NULL)
		e->envp[i] = ft_strjoin(ft_strdup(e->envp[i]), e->av[2]);
	e->envp[i + 1] = NULL;
	init_env(e);
	return (1);
}
