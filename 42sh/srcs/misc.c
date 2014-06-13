/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 13:53:22 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sh42.h>

void			display_name(void)
{
	ft_putstr("\033[1;31m");
	ft_putendl(" _  _  ____      _     ");
	ft_putendl("| || ||___ \\ ___| |__  ");
	ft_putendl("| || |_ __| / __| '_ \\ ");
	ft_putendl("|__   _/ __/\\__ \\ | | |");
	ft_putendl("   |_||_____|___/_| |_|");
	ft_putstr("\033[0m");
	ft_putchar('\n');
}

void			display_help(void)
{
	ft_putstr("\033[1;31m");
	ft_putendl("#---------------------------------------------------#");
	ft_putstr("|       \033[1;33m          42sh - version 4.0");
	ft_putendl("\033[1;31m                |");
	ft_putendl("| How to use :                                      |");
	ft_putendl("| - shift + left/right : move word by word          |");
	ft_putendl("| - shift + up/down : move line by line             |");
	ft_putendl("| - home/end : go to the beginning/end of the line  |");
	ft_putendl("| - alt + arrows : select                           |");
	ft_putendl("| - alt + c : copy                                  |");
	ft_putendl("| - alt + x : cut                                   |");
	ft_putendl("| - alt + v : paste                                 |");
	ft_putendl("#---------------------------------------------------#");
	ft_putendl("\033[0m");
}

void			get_prompt(t_env *e, t_termcap *t)
{
	if (t->prompt)
		free(t->prompt);
	if (t->shell == SHELL)
	{
		t->prompt = ft_strdup(e->pwd);
		if (ft_strcmp(t->prompt, e->home) == 0)
			t->prompt = ft_strdup("~");
		else
		{
			t->prompt = ft_strrchr(t->prompt, '/');
			if (ft_strcmp(t->prompt, "/") != 0)
				t->prompt = ft_strsub(t->prompt, 1, ft_strlen(t->prompt));
		}
		ft_putstr_fd("\033[1;32m", 1);
		ft_putstr_fd(t->prompt, 1);
		ft_putstr_fd("\033[0m", 1);
		ft_putstr_fd(" % ", 1);
		t->prompt = ft_strjoin(t->prompt, " % ");
	}
	else
	{
		t->prompt = ft_strdup("> ");
		ft_putstr_fd(t->prompt, 1);
	}
}
