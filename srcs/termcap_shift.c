/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_shift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 12:21:18 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <termcap.h>

int				key_shup(t_termcap *t)
{
	int			i;

	i = t->co;
	if (t->cur_line > 0)
	{
		while (i > 0)
		{
			key_left(t);
			i--;
		}
	}
	return (0);
}

int				key_shdown(t_termcap *t)
{
	int			i;

	i = 0;
	if ((int)(ft_strlen(t->cmd) + ft_strlen(t->prompt)) / t->co > 0)
	{
		while (i < t->co)
		{
			key_right(t);
			i++;
		}
	}
	return (0);
}

int				key_shleft(t_termcap *t)
{
	while (t->cmd[t->cur_char - 1] == ' ')
		key_left(t);
	while (t->cmd[t->cur_char - 1] != ' ' && t->cur_char > 0)
		key_left(t);
	return (0);
}

int				key_shright(t_termcap *t)
{
	while (t->cmd[t->cur_char] == ' ')
		key_right(t);
	while (t->cmd[t->cur_char] != ' ' && t->cmd[t->cur_char] != '\0')
		key_right(t);
	return (0);
}
