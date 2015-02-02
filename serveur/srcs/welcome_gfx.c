/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_gfx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 11:55:15 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/13 11:58:15 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

void		send_teams(t_list *list, int cs)
{
	while (list)
	{
		dprintf(cs, "tna %s\n", ((t_team *)(list->content))->name);
		list = list->next;
	}
}

static void	send_players(t_list *list, int cs)
{
	t_list	*players;

	while (list)
	{
		players = ((t_team *)(list->content))->players;
		while (players)
		{
			dprintf(cs, "pnw #%d %d %d %d %d %s\n",
					((t_player *)players->content)->id,
					((t_player *)players->content)->x,
					((t_player *)players->content)->y,
					((t_player *)players->content)->orientation,
					((t_player *)players->content)->level,
					((t_player *)players->content)->team);
			players = players->next;
		}
		list = list->next;
	}
}

static void	send_eggs(t_list *list, int cs)
{
	while (list)
	{
		dprintf(cs, "enw #%d #%d %d %d\n", ((t_egg *)list->content)->id,
				((t_egg *)list->content)->player, ((t_egg *)list->content)->x,
				((t_egg *)list->content)->y);
		list = list->next;
	}
}

void		welcome(t_env *e, t_net *net, int cs)
{
	net->fd_graphic = cs;
	dprintf(cs, "msz %d %d\n", e->width, e->height);
	dprintf(cs, "sgt %d\n", (int)e->time);
	send_map(e, cs, 0);
	send_teams(e->teams, cs);
	send_players(e->teams, cs);
	send_eggs(e->eggs, cs);
}
