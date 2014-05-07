/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 15:46:05 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 16:05:16 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <termcap.h>
#include <sh42.h>

void		add_or_create_list_history(t_termcap *t, char *str)
{
	if (t->history == NULL)
		t->history = ft_dllstnew(str, ft_strlen(str) + 1);
	else
		ft_dllstadd(&(t->history), ft_dllstnew(str, ft_strlen(str) + 1));
}

static int	key_ret_found(t_termcap *t, int *found, int i, char *buff)
{
	if (t->shell == SHELL && t->keys[i].f(t))
		return (1);
	else if (t->shell != SHELL && ft_strcmp(buff, "\n") != 0)
		t->keys[i].f(t);
	else if (t->shell == SUBSHELL && ft_strcmp(buff, "\n") == 0)
		*found = 2;
	else if (t->shell == HERESHELL && ft_strcmp(buff, "\n") == 0)
		*found = 3;
	if (t->start != -1 && t->keys[i].f != &key_altleft
		&& t->keys[i].f != &key_altright)
	{
		tputs(tgetstr("sc", NULL), 1, ft_output);
		rewrite_cmd(t);
		tputs(tgetstr("rc", NULL), 1, ft_output);
		t->start = -1;
		t->end = -1;
	}
	return (0);
}

static int	is_alt_code2(t_termcap *t, int *found, char *buff)
{
	if ((unsigned char)buff[0] == 226 && (unsigned char)buff[1] == 136
		&& (unsigned char)buff[2] == 154)
	{
		*found = 1;
		if (t->list_cmpl)
		{
			free_list_completion(&t->list_cmpl);
			t->list_cmpl = NULL;
		}
		t->tab = 0;
		return (17);
	}
	return (0);
}

static int	is_alt_code(t_termcap *t, int *found, char *buff)
{
	if ((unsigned char)buff[0] == 226 && (unsigned char)buff[1] == 137
		&& (unsigned char)buff[2] == 136)
	{
		*found = 1;
		if (t->list_cmpl)
		{
			free_list_completion(&t->list_cmpl);
			t->list_cmpl = NULL;
		}
		t->tab = 0;
		return (15);
	}
	else if ((unsigned char)buff[0] == 195 && (unsigned char)buff[1] == 167
			&& (unsigned char)buff[2] == 0)
	{
		*found = 1;
		if (t->list_cmpl)
		{
			free_list_completion(&t->list_cmpl);
			t->list_cmpl = NULL;
		}
		t->tab = 0;
		return (16);
	}
	return (is_alt_code2(t, found, buff));
}

int			compare_to_tab_key(t_termcap *t, int *found, char *buff)
{
	int		i;

	if (!(i = is_alt_code(t, found, buff)))
	{
		while (i < NB_KEYS)
		{
			if (ft_memcmp(buff, t->keys[i].key, ft_strlen(t->keys[i].key)) == 0)
			{
				if ((*found = 1) && ft_strcmp(buff, "\011") != 0)
				{
					if (t->list_cmpl)
					{
						free_list_completion(&t->list_cmpl);
						t->list_cmpl = NULL;
					}
					t->tab = 0;
				}
				break ;
			}
			i++;
		}
	}
	if (*found == 1 && key_ret_found(t, found, i, buff))
		return (1);
	return (0);
}
