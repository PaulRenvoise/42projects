/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 13:00:37 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

int			builtin_echo(t_env *e, int fd)
{
	int		i;
	int		check;

	check = 0;
	i = 1;
	if (e->av[1] != NULL)
	{
		if (ft_strcmp(e->av[1], "-n") == 0)
		{
			i = 2;
			check = 1;
		}
		while (e->av[i] != NULL)
		{
			ft_putstr_fd(e->av[i], fd);
			if (e->av[i + 1] != NULL)
				ft_putchar_fd(' ', fd);
			i++;
		}
		if (check == 1)
			return (1);
	}
	ft_putchar_fd('\n', fd);
	return (1);
}
