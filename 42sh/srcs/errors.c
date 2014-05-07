/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 15:10:00 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

void			print_err(char *info, int errcode)
{
	if (errcode == MALLOC)
	{
		ft_printf_fd("%s failed", 2, info);
		reset_term(get_termcap(), 0);
		exit(errcode);
	}
	else if (errcode == TERM)
	{
		ft_printf_fd("Terminal not found\n", 2);
		exit(errcode);
	}
	else if (errcode == GETENT)
	{
		ft_printf_fd("Getent() failed\n", 2);
		exit(errcode);
	}
}
