/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 12:18:23 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 18:41:26 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <termcap.h>

int				key_right(t_termcap *t)
{
	if (t->cur_char != (int)ft_strlen(t->cmd))
	{
		if (t->cur_col + 1 < t->co)
		{
			tputs(tgetstr("nd", NULL), 1, ft_output);
			t->cur_col++;
		}
		else
		{
			t->cur_col = 0;
			t->cur_line++;
			tputs(tgetstr("do", NULL), 1, ft_output);
		}
		t->cur_char++;
	}
	return (0);
}

int				key_left(t_termcap *t)
{
	if (t->cur_col > (int)ft_strlen(t->prompt) && t->cur_line == 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_output);
		t->cur_char--;
		t->cur_col--;
	}
	else if (t->cur_line > 0)
	{
		if (t->cur_col > 0)
		{
			tputs(tgetstr("le", NULL), 1, ft_output);
			t->cur_char--;
			t->cur_col--;
		}
		else
		{
			t->cur_line--;
			t->cur_char--;
			tputs(tgetstr("up", NULL), 1, ft_output);
			t->cur_col = t->co - 1;
			tputs(tgoto(tgetstr("ch", NULL), t->cur_col, t->cur_col),
					1, ft_output);
		}
	}
	return (0);
}

int				key_up(t_termcap *t)
{
	if (t->history != NULL && t->history->prev == NULL)
		add_or_create_list_history(t, t->cmd);
	if (t->history != NULL)
	{
		if (t->history->next != NULL)
			t->history = t->history->next;
		key_end(t);
		t->cmd = ft_strdup(((char *)(t->history->content)));
		rewrite_cmd(t);
		t->cur_char = (int)ft_strlen(t->cmd);
		if (!t->cur_line)
			t->cur_col = (int)(ft_strlen(t->cmd) + ft_strlen(t->prompt));
		else
			t->cur_col = (int)(ft_strlen(t->cmd) + ft_strlen(t->prompt))
						% t->co;
	}
	return (0);
}

int				key_down(t_termcap *t)
{
	if (t->history != NULL && t->history->prev != NULL)
	{
		t->history = (t->history)->prev;
		key_end(t);
		t->cmd = ft_strdup(((char *)(t->history->content)));
		rewrite_cmd(t);
		t->cur_char = (int)ft_strlen(t->cmd);
		if (t->history->prev == NULL)
			ft_dllstdelitem(&t->history);
		if (!t->cur_line)
			t->cur_col = (int)(ft_strlen(t->cmd) + ft_strlen(t->prompt));
		else
			t->cur_col = (int)(ft_strlen(t->cmd) + ft_strlen(t->prompt))
						% t->co;
	}
	return (0);
}

int				key_altright(t_termcap *t)
{
	if (t->start == -1)
		t->start = t->cur_char;
	t->end = t->cur_char;
	if (t->cur_char < (int)ft_strlen(t->cmd))
	{
		if (t->start > t->cur_char)
		{
			tputs(tgetstr("dc", NULL), 1, ft_output);
			ft_output(t->cmd[t->cur_char]);
			tputs(tgetstr("le", NULL), 1, ft_output);
			key_right(t);
		}
		else
		{
			tputs(tgetstr("dc", NULL), 1, ft_output);
			tputs(tgetstr("mr", NULL), 1, ft_output);
			ft_output(t->cmd[t->cur_char]);
			tputs(tgetstr("me", NULL), 1, ft_output);
			tputs(tgetstr("le", NULL), 1, ft_output);
			key_right(t);
		}
	}
	return (0);
}
