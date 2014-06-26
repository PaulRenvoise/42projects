/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/07 16:40:50 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/16 18:23:54 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

static void		move_player(t_env *e, t_player *player)
{
	if (player->orientation == NORD)
	{
		player->y += 1;
		if (player->y >= e->height)
			player->y = 0;
	}
	else if (player->orientation == EST)
	{
		player->x += 1;
		if (player->x >= e->width)
			player->x = 0;
	}
	else if (player->orientation == SUD)
	{
		player->y -= 1;
		if (player->y < 0)
			player->y = e->height - 1;
	}
	else if (player->orientation == OUEST)
	{
		player->x -= 1;
		if (player->x < 0)
			player->x = e->width - 1;
	}
}

void			forward(t_player *player, t_env *e, t_net *net)
{
	if (ft_strcmp(net->fds[player->id].buf_read, "avance\n") == 0)
	{
		move_player(e, player);
		dprintf(net->fd_graphic, "ppo #%d %d %d %d\n", player->id, player->x,
				player->y, player->orientation);
		ft_lstadd_or_create(e, "ok\n", player->id, 7 / e->time);
	}
}

void			right(t_player *player, t_env *e, t_net *net)
{
	if (ft_strcmp(net->fds[player->id].buf_read, "droite\n") == 0)
	{
		player->orientation += 1;
		if (player->orientation > 4)
			player->orientation = 1;
		dprintf(net->fd_graphic, "ppo #%d %d %d %d\n", player->id, player->x,
				player->y, player->orientation);
		ft_lstadd_or_create(e, "ok\n", player->id, 7 / e->time);
	}
}

void			left(t_player *player, t_env *e, t_net *net)
{
	if (ft_strcmp(net->fds[player->id].buf_read, "gauche\n") == 0)
	{
		player->orientation -= 1;
		if (player->orientation < 1)
			player->orientation = 4;
		dprintf(net->fd_graphic, "ppo #%d %d %d %d\n", player->id, player->x,
				player->y, player->orientation);
		ft_lstadd_or_create(e, "ok\n", player->id, 7 / e->time);
	}
}
