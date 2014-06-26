/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 10:39:16 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:14:36 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

static void	check_if_live(t_player *player, t_list *head, t_net *net,
				float ftime)
{
	player->inventory[0] -= 1;
	dprintf(net->fd_graphic, "pin #%d %d %d %d %d %d %d %d %d %d\n",
			player->id, player->x, player->y, player->inventory[0],
			player->inventory[1], player->inventory[2],
			player->inventory[3], player->inventory[4],
			player->inventory[5], player->inventory[6]);
	if (player->inventory[0] == 0)
	{
		ft_strcpy(net->fds[player->id].buf_write
					+ ft_strlen(net->fds[player->id].buf_write), "mort\n");
		dprintf(net->fd_graphic, "pdi #%d\n", player->id);
		delete_player(head, player->id);
	}
	else
		player->time += (int)(1000000 * ftime);
}

void		lose_life(t_list *list, t_env *e, t_net *net, unsigned long time)
{
	t_list	*players;
	t_list	*head;
	float	ftime;

	ftime = 126 / e->time;
	head = list;
	while (list)
	{
		players = ((t_team *)(list->content))->players;
		while (players)
		{
			if (time >= ((t_player *)players->content)->time)
				check_if_live(((t_player *)players->content), head, net, ftime);
			players = players->next;
		}
		list = list->next;
	}
}
