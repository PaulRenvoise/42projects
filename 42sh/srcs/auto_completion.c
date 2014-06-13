/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 18:21:25 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <termcap.h>

static void			check_type_cmpl(t_termcap *t, int *i, t_list **list)
{
	*list = lexer(ft_strsub(t->cmd, 0, (size_t)t->cur_char));
	*i = 0;
	while (*list && (*list)->next)
	{
		(*i)++;
		if (((get_tk(*list)->type) == SM_CL
					|| (get_tk(*list)->type) == PIPE))
			*i = 0;
		*list = (*list)->next;
	}
}

static void			complet_list_cmplt_cmd(t_termcap *t, t_list **list)
{
	ft_btree_search_node(&(t->list_cmpl),
			t->completion->root, get_tk(*list)->text, &ft_strncmp);
	t->head_completion = t->list_cmpl;
	t->tab = 1;
}

static void			move_in_list_cmplt(t_termcap *t)
{
	int				i;
	t_dllist		*list_tmp;
	char			*tmp;

	list_tmp = (ft_dllstgetitemat(t->list_cmpl, (unsigned int)t->tab));
	if (list_tmp == NULL)
	{
		t->tab = 1;
		list_tmp = (ft_dllstgetitemat(t->list_cmpl, (unsigned int)t->tab));
	}
	tmp = ft_strdup(list_tmp->content);
	while (t->cur_char > 0 && (t->cmd[t->cur_char - 1] != ' '
				&& t->cmd[t->cur_char - 1] != '|'
				&& t->cmd[t->cur_char - 1] != ';'
				&& t->cmd[t->cur_char - 1] != '/'))
		key_delete(t);
	t->cmd[t->cur_char] = '\0';
	i = 0;
	while (i < (int)ft_strlen(tmp))
	{
		print_char(t, tmp[i]);
		i++;
	}
	t->tab++;
}

int					key_tab(t_termcap *t)
{
	int				i;
	t_list			*list;

	list = NULL;
	if (t->tab == 0)
	{
		check_type_cmpl(t, &i, &list);
		if (list && i == 0 && ft_strchr(get_tk(list)->text, '/') == NULL
			&& t->cmd[t->cur_char - 1] != ' ')
			complet_list_cmplt_cmd(t, &list);
		else
		{
			if (i >= 0 && t->cmd[t->cur_char - 1] == ' ')
				create_list_completion(t, NULL);
			else if (list)
				create_list_completion(t, get_tk(list)->text);
			t->tab = 1;
		}
	}
	if (t->list_cmpl)
		move_in_list_cmplt(t);
	if (list)
		free_list(&list);
	return (0);
}
