/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:00:41 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/12 16:01:09 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>

void		del_elem_list(t_list **begin, t_list *to_del)
{
	t_list		*prev;
	t_list		*tmp;

	prev = NULL;
	tmp = *begin;
	while (tmp)
	{
		if (tmp == to_del)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*begin = tmp->next;
			ft_lstdelone(&tmp, ft_lstdel_elem);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void		delete_player(t_list *list, int id)
{
	t_list	*players;

	while (list)
	{
		players = ((t_team *)(list->content))->players;
		while (players)
		{
			if (((t_player *)players->content)->id == id)
				del_elem_list(&((t_team *)(list->content))->players, players);
			players = players->next;
		}
		list = list->next;
	}
}
