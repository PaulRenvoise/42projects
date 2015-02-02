/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 12:33:50 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <termcap.h>
#include <stdlib.h>

int				key_home(t_termcap *t)
{
	while (t->cur_line > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_output);
		t->cur_line--;
	}
	t->cur_col = (int)ft_strlen(t->prompt);
	tputs(tgoto(tgetstr("ch", NULL), t->cur_col, t->cur_col), 1, ft_output);
	t->cur_char = 0;
	return (0);
}

int				key_end(t_termcap *t)
{
	while (t->cur_line < (int)ft_strlen(t->cmd) / t->co)
	{
		tputs(tgetstr("do", NULL), 1, ft_output);
		t->cur_line++;
	}
	t->cur_col = (int)(ft_strlen(t->cmd) + ft_strlen(t->prompt)) % t->co;
	tputs(tgoto(tgetstr("ch", NULL), t->cur_col, t->cur_col), 1, ft_output);
	t->cur_char = (int)ft_strlen(t->cmd);
	return (0);
}

int				key_ctrld(t_termcap *t)
{
	reset_term(t, 1);
	free_all(t, get_env());
	exit(0);
	return (0);
}

int				key_ret(t_termcap *t)
{
	if (ft_strcmp("", t->cmd) != 0 && notonlyspace(t->cmd))
	{
		t->history = t->head;
		add_or_create_list_history(t, t->cmd);
		t->head = t->history;
	}
	rewrite_cmd(t);
	t->cur_col = 0;
	t->cur_char = 0;
	t->cur_line = 0;
	ft_putchar_fd('\n', 0);
	return (1);
}
