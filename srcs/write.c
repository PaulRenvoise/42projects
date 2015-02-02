/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:28:39 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 18:50:04 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <termcap.h>
#include <stdlib.h>
#include <unistd.h>

int				ft_output(int c)
{
	write(1, &c, 1);
	return (0);
}

void			rewrite_cmd(t_termcap *t)
{
	int			i;

	i = t->cur_line;
	while (i >= 0)
	{
		tputs(tgetstr("dl", NULL), 1, ft_output);
		if (i > 0)
			tputs(tgetstr("up", NULL), 1, ft_output);
		i--;
	}
	tputs(tgetstr("cr", NULL), 1, ft_output);
	get_prompt(get_env(), t);
	ft_putstr_fd(t->cmd, 1);
	t->cur_line = (int)(ft_strlen(t->cmd) + ft_strlen(t->prompt)) / t->co;
}

void			print_char(t_termcap *t, char c)
{
	int			size;

	size = (int)ft_strlen(t->cmd) + 1;
	if (!(t->cmd = (char *)ft_realloc(t->cmd, sizeof(char)
										* (size_t)(size + 1))))
		print_err("Realloc()", MALLOC);
	while (size > t->cur_char)
	{
		t->cmd[size] = t->cmd[size - 1];
		size--;
	}
	t->cmd[t->cur_char] = c;
	key_right(t);
	tputs(tgetstr("sc", NULL), 1, ft_output);
	rewrite_cmd(t);
	t->cur_line = (int)(t->cur_char + ft_strlen(t->prompt)) / t->co;
	tputs(tgetstr("rc", NULL), 1, ft_output);
}
