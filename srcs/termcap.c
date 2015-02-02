/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 15:46:38 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 15:39:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termcap.h>
#include <unistd.h>
#include <libft.h>
#include <sh42.h>

static void		init_look_key(t_termcap *t)
{
	if (t->shell != SHELL)
		get_prompt(get_env(), t);
	t->cur_char = 0;
	t->cur_col = (int)ft_strlen(t->prompt);
	t->cur_line = 0;
	t->tab = 0;
	t->start = -1;
	t->end = -1;
	t->co = tgetnum("co");
	t->cmd = NULL;
	if (!(t->cmd = (char *)malloc(sizeof(char))))
		print_err("Malloc()", MALLOC);
	t->cmd[0] = '\0';
}

static int		found_two(t_termcap *t, char *end)
{
	int			j;

	j = 0;
	ft_putchar('\n');
	t->cmd_subshell = ft_strjoin(t->cmd_subshell, "\n");
	t->cmd_subshell = ft_strjoin(t->cmd_subshell, t->cmd);
	while (t->cmd[j] != '\0')
	{
		if (t->cmd[j] == *end)
			return (1);
		j++;
	}
	if (t->cmd)
		free(t->cmd);
	t->cmd = NULL;
	if (!(t->cmd = (char *)malloc(sizeof(char))))
		print_err("Malloc()", MALLOC);
	t->cmd[0] = '\0';
	t->cur_char = 0;
	t->cur_col = (int)ft_strlen(t->prompt);
	t->cur_line = 0;
	return (0);
}

static int		found_three(t_termcap *t, char *end)
{
	ft_putchar('\n');
	if (ft_strcmp(t->cmd, end) == 0)
		return (1);
	ft_putendl_fd(t->cmd, t->heredoc_fd);
	if (t->cmd)
		free(t->cmd);
	t->cmd = NULL;
	if (!(t->cmd = (char *)malloc(sizeof(char))))
		print_err("Malloc()", MALLOC);
	t->cmd[0] = '\0';
	t->cur_char = 0;
	t->cur_col = (int)ft_strlen(t->prompt);
	t->cur_line = 0;
	return (0);
}

static int		return_pressed(t_termcap *t, int found, char *buff, char *end)
{
	t->start = -1;
	t->end = -1;
	t->tab = 0;
	if (t->list_cmpl)
	{
		free_list_completion(&t->list_cmpl);
		t->list_cmpl = NULL;
	}
	if (found == 2)
	{
		if (found_two(t, end))
			return (1);
	}
	else if (found == 3)
	{
		if (found_three(t, end))
			return (1);
	}
	if (ft_isprint(buff[0]) && found == 0)
		print_char(t, buff[0]);
	if (found >= 2)
		get_prompt(get_env(), t);
	return (0);
}

char			*look_key(t_termcap *t, char *end)
{
	int			found;
	char		buff[NB_READ_KEY];

	init_look_key(t);
	while (1)
	{
		ft_memset(buff, 0, NB_READ_KEY);
		read(0, buff, NB_READ_KEY - 1);
		buff[NB_READ_KEY - 1] = '\0';
		found = 0;
		if (compare_to_tab_key(t, &found, buff))
			return (t->cmd);
		if (found != 1)
		{
			if (return_pressed(t, found, buff, end))
				return (t->cmd);
		}
	}
	return (NULL);
}
