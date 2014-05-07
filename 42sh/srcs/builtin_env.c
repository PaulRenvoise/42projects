/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:25:07 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

int			builtin_env(t_env *e, int fd)
{
	int		i;
	t_fd	fdt;

	if (e->av[1] != NULL)
	{
		fdt.fd_out = fd;
		fdt.fd_in = 0;
		if (!check_cmd(e, &fdt))
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(e->av[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
		return (0);
	}
	i = 0;
	while (e->envp[i])
	{
		ft_putendl_fd(e->envp[i], fd);
		i++;
	}
	return (1);
}
