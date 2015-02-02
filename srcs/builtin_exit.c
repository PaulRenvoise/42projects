/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:25:20 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

int			builtin_exit(t_env *e, int fd)
{
	(void)fd;
	reset_term(get_termcap(), 1);
	free_all(get_termcap(), get_env());
	if (e->av[1] != NULL)
		exit(ft_atoi(e->av[1]));
	else
		exit(0);
	return (0);
}
