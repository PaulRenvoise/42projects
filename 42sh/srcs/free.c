/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 17:53:29 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

void			free_tree(t_cmd_tree **root)
{
	int			i;

	i = 0;
	if (*root)
	{
		free_tree(&(*root)->left);
		while ((*root)->av && (*root)->av[i])
		{
			free((*root)->av[i]);
			i++;
		}
		i = 1;
		while ((*root)->files && (*root)->files[i])
		{
			free(((*root)->files[i])->text);
			i++;
		}
		free_tree(&(*root)->right);
	}
}

void			free_list(t_list **list)
{
	if (*list)
	{
		while (*list)
		{
			free(get_tk(*list)->text);
			*list = (*list)->next;
		}
		free(*list);
	}
}

void			free_list_completion(t_dllist **list)
{
	if (*list)
	{
		while (*list)
		{
			free((*list)->content);
			*list = (*list)->next;
		}
		free(*list);
	}
}

void			free_all(t_termcap *t, t_env *e)
{
	int			i;

	i = 0;
	free_list_completion(&t->list_cmpl);
	free_list_completion(&t->head);
	free_list_completion(&t->history);
	if (t->cmd)
		free(t->cmd);
	if (t->clipboard)
		free(t->clipboard);
	free(e->home);
	free(e->paths);
	free(e->pwd);
	free(e->user);
	free(e->pwd_old);
	while (i < NB_KEYS)
	{
		free(t->keys[i].key);
		i++;
	}
	while (i < NB_BUILT_IN)
	{
		free(e->builtin[i].name);
		i++;
	}
}
