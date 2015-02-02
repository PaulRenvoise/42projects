/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 12:35:38 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 19:14:26 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <sh42.h>
#include <stdlib.h>

int				key_delete(t_termcap *t)
{
	int			size;
	int			i;

	size = (int)ft_strlen(t->cmd) + 1;
	i = t->cur_char - 1;
	if (t->cur_char > 0)
	{
		key_left(t);
		if (!(t->cmd = (char*)ft_realloc(t->cmd, sizeof(char)
											* (size_t)(size - 1))))
			print_err("Realloc()", MALLOC);
		while (i < (size - 1))
		{
			t->cmd[i] = t->cmd[i + 1];
			i++;
		}
		t->cmd[i - 1] = '\0';
	}
	tputs(tgetstr("sc", NULL), 1, ft_output);
	rewrite_cmd(t);
	t->cur_line = (int)(t->cur_char + ft_strlen(t->prompt)) / t->co;
	tputs(tgetstr("rc", NULL), 1, ft_output);
	return (0);
}

int				key_del(t_termcap *t)
{
	int			size;
	int			i;

	size = (int)ft_strlen(t->cmd) + 1;
	i = t->cur_char;
	if (t->cur_char != size - 1)
	{
		if (!(t->cmd = (char*)ft_realloc(t->cmd, sizeof(char)
											* (size_t)(size - 1))))
			print_err("Realloc()", MALLOC);
		while (i < (size - 1))
		{
			t->cmd[i] = t->cmd[i + 1];
			i++;
		}
		t->cmd[i - 1] = '\0';
	}
	tputs(tgetstr("sc", NULL), 1, ft_output);
	rewrite_cmd(t);
	t->cur_line = (int)(t->cur_char + ft_strlen(t->prompt)) / t->co;
	tputs(tgetstr("rc", NULL), 1, ft_output);
	return (0);
}
