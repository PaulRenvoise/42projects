/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_alt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 12:07:50 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 18:59:30 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <termcap.h>
#include <stdlib.h>

int				key_altc(t_termcap *t)
{
	int			i;

	if (t->start != -1 && t->end != -1)
	{
		i = (t->start <= t->end ? t->start : t->end);
		if (t->start > t->end)
			i--;
		if (t->clipboard)
			free(t->clipboard);
		t->clipboard = ft_strsub(t->cmd, (unsigned int)i,
									(size_t)(abs(t->end - t->start) + 1));
	}
	return (0);
}

int				key_altx(t_termcap *t)
{
	int			i;
	int			j;

	if (!key_altc(t) && t->start != -1 && t->end != -1)
	{
		if (t->start > t->end)
		{
			i = t->start;
			j = t->end;
		}
		else
		{
			i = t->end;
			j = t->start;
		}
		while (i >= j)
		{
			if (t->start > t->end)
				key_del(t);
			else
				key_delete(t);
			i--;
		}
	}
	return (0);
}

int				key_altv(t_termcap *t)
{
	int			i;

	i = 0;
	while (t->clipboard && i < (int)ft_strlen(t->clipboard))
	{
		print_char(t, t->clipboard[i]);
		i++;
	}
	t->start = -1;
	t->end = -1;
	return (0);
}

static void		altleft_utils(t_termcap *t, int call, int hl)
{
	if (hl)
		tputs(tgetstr("mr", NULL), 1, ft_output);
	ft_output(t->cmd[t->cur_char - 1]);
	if (t->cur_char + (int)ft_strlen(t->prompt) == t->co)
	{
		tputs(tgetstr("do", NULL), 1, ft_output);
		tputs(tgetstr("cr", NULL), 1, ft_output);
		t->cur_col = 0;
		call = 1;
	}
	if (!t->cur_col && !call)
		tputs(tgetstr("do", NULL), 1, ft_output);
	if (hl)
		tputs(tgetstr("me", NULL), 1, ft_output);
	key_left(t);
}

int				key_altleft(t_termcap *t)
{
	int			call;

	call = 0;
	if (t->start == -1)
		t->start = t->cur_char;
	t->end = t->cur_char;
	if (t->cur_char > 0)
	{
		if (!t->cur_col)
		{
			tputs(tgetstr("up", NULL), 1, ft_output);
			t->cur_col = t->co - 1;
			tputs(tgoto(tgetstr("ch", NULL), t->cur_col, t->cur_col),
						1, ft_output);
		}
		else
			tputs(tgetstr("le", NULL), 1, ft_output);
		tputs(tgetstr("dc", NULL), 1, ft_output);
		if (t->start < t->cur_char)
			altleft_utils(t, call, 0);
		else
			altleft_utils(t, call, 1);
	}
	return (0);
}
