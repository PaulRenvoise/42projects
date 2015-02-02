/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eject.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 12:02:20 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/11 17:28:22 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

static void	send_message_client(t_env *e, t_player *player,
				t_player *player_tile)
{
	if (player->orientation == NORD)
	{
		dprintf(player_tile->id, "deplacement %d\n", 3);
		player_tile->y += 1;
		player_tile->y = (player_tile->y >= e->height ? 0 : player_tile->y);
	}
	else if (player->orientation == EST)
	{
		dprintf(player_tile->id, "deplacement %d\n", 4);
		player_tile->x += 1;
		player_tile->x = (player_tile->x >= e->width ? 0 : player_tile->x);
	}
	else if (player->orientation == SUD)
	{
		dprintf(player_tile->id, "deplacement %d\n", 1);
		player_tile->y -= 1;
		player_tile->y = (player_tile->y < 0 ? e->height - 1 : player_tile->y);
	}
	else if (player->orientation == OUEST)
	{
		dprintf(player_tile->id, "deplacement %d\n", 2);
		player_tile->x -= 1;
		player_tile->x = (player_tile->x < 0 ? e->width - 1 : player_tile->x);
	}
}

void		eject(t_player *player, t_env *e, t_net *net)
{
	t_player	*player_tile;

	if (ft_strcmp(net->fds[player->id].buf_read, "expulse\n") == 0)
	{
		if (get_player_at_pos(e->teams, player->x, player->y,
					player->id) == NULL)
			ft_lstadd_or_create(e, "ko\n", player->id, 7 / e->time);
		else
		{
			dprintf(net->fd_graphic, "pex #%d\n", player->id);
			while ((player_tile = get_player_at_pos(e->teams, player->x,
					player->y, player->id)) != NULL)
			{
				send_message_client(e, player, player_tile);
				dprintf(net->fd_graphic, "ppo #%d %d %d %d\n", player_tile->id,
					player_tile->x, player_tile->y, player_tile->orientation);
			}
			ft_lstadd_or_create(e, "ok\n", player->id, 7 / e->time);
		}
	}
}
