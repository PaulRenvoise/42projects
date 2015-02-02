/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 15:13:12 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/12 15:14:32 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>

t_player	*get_player(t_list *list, int id)
{
	t_list	*players;

	while (list)
	{
		players = ((t_team *)(list->content))->players;
		while (players)
		{
			if (((t_player *)players->content)->id == id)
				return ((t_player *)players->content);
			players = players->next;
		}
		list = list->next;
	}
	return (NULL);
}

t_player	*get_player_at_pos(t_list *list, int x, int y, int id)
{
	t_list	*players;

	while (list)
	{
		players = ((t_team *)(list->content))->players;
		while (players)
		{
			if (((t_player *)players->content)->x == x
				&& ((t_player *)players->content)->y == y
				&& ((t_player *)players->content)->id != id)
				return ((t_player *)players->content);
			players = players->next;
		}
		list = list->next;
	}
	return (NULL);
}

int			get_player_pos_voir(t_list *list, int x, int y, int id)
{
	t_list	*players;
	int		i;

	i = 0;
	while (list)
	{
		players = ((t_team *)(list->content))->players;
		while (players)
		{
			if (((t_player *)players->content)->x == x
				&& ((t_player *)players->content)->y == y
				&& ((t_player *)players->content)->id != id)
				i++;
			players = players->next;
		}
		list = list->next;
	}
	return (i);
}

t_player	*get_player_at_pos_level(t_list *list, int x, int y, int lvl)
{
	t_list	*players;

	while (list)
	{
		players = ((t_team *)(list->content))->players;
		while (players)
		{
			if (((t_player *)players->content)->x == x
				&& ((t_player *)players->content)->y == y
				&& ((t_player *)players->content)->level == lvl)
				return ((t_player *)players->content);
			players = players->next;
		}
		list = list->next;
	}
	return (NULL);
}

int			get_numb_player_at(t_list *list, int x, int y, int lvl)
{
	t_list	*players;
	int		i;

	i = 0;
	while (list)
	{
		players = ((t_team *)(list->content))->players;
		while (players)
		{
			if (((t_player *)players->content)->x == x
				&& ((t_player *)players->content)->y == y
				&& ((t_player *)players->content)->level == lvl)
				i++;
			players = players->next;
		}
		list = list->next;
	}
	return (i);
}
