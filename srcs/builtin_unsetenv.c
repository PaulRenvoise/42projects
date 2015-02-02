/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:25:59 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <string.h>

static void		builtin_unsetenv_clr(t_env *e, int i, int j, int *found)
{
	if (ft_strnstr(e->envp[i], e->av[j], ft_strlen(e->av[j]))
			&& ((e->envp[i])[ft_strlen(e->av[j])]) == '=')
	{
		ft_strclr(e->envp[i]);
		*found = 1;
	}
	if (*found)
		e->envp[i] = ft_strdup(e->envp[i + 1]);
}

int				builtin_unsetenv(t_env *e, int fd)
{
	int		i;
	int		j;
	int		found;

	(void)fd;
	j = 1;
	if (e->av[1] == NULL)
	{
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return (0);
	}
	while (e->av[j])
	{
		i = 0;
		found = 0;
		while (e->envp[i])
		{
			builtin_unsetenv_clr(e, i, j, &found);
			i++;
		}
		e->envp[i] = NULL;
		j++;
	}
	return (0);
}
