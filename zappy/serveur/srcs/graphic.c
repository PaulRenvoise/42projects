/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 10:47:42 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/25 13:40:41 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

void	gfx_pin(t_env *e, t_net *net, int cs)
{
	char		**tab;
	t_player	*player;

	tab = ft_strsplit(net->fds[cs].buf_read, ' ');
	if ((player = get_player(e->teams, ft_atoi(tab[1] + 1)))
				&& player != NULL)
	{
		dprintf(cs, "pin #%d %d %d %d %d %d %d %d %d %d\n", player->id,
		player->x, player->y, player->inventory[0], player->inventory[1],
		player->inventory[2], player->inventory[3], player->inventory[4],
		player->inventory[5], player->inventory[6]);
	}
}

void	gfx_next(t_env *e, t_net *net, int cs)
{
	char		**tab;
	t_player	*player;

	if (ft_strncmp(net->fds[cs].buf_read, "ppo", 3) == 0)
	{
		tab = ft_strsplit(net->fds[cs].buf_read, ' ');
		if ((player = get_player(e->teams, ft_atoi(tab[1] + 1)))
			&& player != NULL)
			dprintf(cs, "ppo #%d %d %d %d\n", player->id, player->x, player->y,
				player->orientation);
	}
	if (ft_strncmp(net->fds[cs].buf_read, "plv", 3) == 0)
	{
		tab = ft_strsplit(net->fds[cs].buf_read, ' ');
		if ((player = get_player(e->teams, ft_atoi(tab[1] + 1)))
			&& player != NULL)
			dprintf(cs, "plv #%d %d\n", player->id, player->level);
	}
	if (ft_strncmp(net->fds[cs].buf_read, "pin", 3) == 0)
		gfx_pin(e, net, cs);
}

void	gfx_next_again(t_env *e, t_net *net, int cs)
{
	char		**tab;

	if (ft_strcmp(net->fds[cs].buf_read, "sgt\n") == 0)
		dprintf(cs, "sgt %d\n", (int)e->time);
	if (ft_strncmp(net->fds[cs].buf_read, "sst", 3) == 0)
	{
		tab = ft_strsplit(net->fds[cs].buf_read, ' ');
		e->time = ft_atoi(tab[1]);
		dprintf(cs, "sgt %d\n", (int)e->time);
	}
}

void	gfx_commands(t_env *e, t_net *net, int cs)
{
	char		**tab;
	int			x;
	int			y;

	if (ft_strcmp(net->fds[cs].buf_read, "msz\n") == 0)
		dprintf(cs, "msz %d %d\n", e->width, e->height);
	if (ft_strncmp(net->fds[cs].buf_read, "bct", 3) == 0)
	{
		tab = ft_strsplit(net->fds[cs].buf_read, ' ');
		x = ft_atoi(tab[1]);
		y = ft_atoi(tab[2]);
		dprintf(cs, "bct %d %d %d %d %d %d %d %d %d\n", x, y, e->map[x][y][0],
			e->map[x][y][1], e->map[x][y][2], e->map[x][y][3], e->map[x][y][4],
			e->map[x][y][5], e->map[x][y][6]);
	}
	if (ft_strcmp(net->fds[cs].buf_read, "mct\n") == 0)
		send_map(e, cs, 0);
	if (ft_strcmp(net->fds[cs].buf_read, "tna\n") == 0)
		send_teams(e->teams, cs);
	gfx_next(e, net, cs);
	gfx_next_again(e, net, cs);
}
