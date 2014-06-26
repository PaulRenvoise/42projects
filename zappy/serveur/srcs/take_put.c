/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 11:32:14 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/19 12:09:48 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

static int			inv_selection(char *input)
{
	if (ft_strcmp(input, "nourriture\n") == 0)
		return (0);
	if (ft_strcmp(input, "linemate\n") == 0)
		return (1);
	if (ft_strcmp(input, "deraumere\n") == 0)
		return (2);
	if (ft_strcmp(input, "sibur\n") == 0)
		return (3);
	if (ft_strcmp(input, "mendiane\n") == 0)
		return (4);
	if (ft_strcmp(input, "phiras\n") == 0)
		return (5);
	if (ft_strcmp(input, "thystame\n") == 0)
		return (6);
	return (-1);
}

static void			update_ress(t_env *e, t_player *player, int c)
{
	if (c != 0)
		e->map[player->y][player->x][c] -= 1;
}

void				take(t_player *player, t_env *e, t_net *net)
{
	int		c;

	if (ft_strncmp(net->fds[player->id].buf_read, "prend", 5) == 0)
	{
		c = inv_selection(ft_strsplit(net->fds[player->id].buf_read, ' ')[1]);
		if (c != -1 && e->map[player->y][player->x][c] != 0)
		{
			player->inventory[c] += 1;
			update_ress(e, player, c);
			dprintf(net->fd_graphic, "pgt #%d %d\n", player->id, c);
			dprintf(net->fd_graphic, "pin #%d %d %d %d %d %d %d %d %d %d\n",
			player->id, player->x, player->y, player->inventory[0],
			player->inventory[1], player->inventory[2],
			player->inventory[3], player->inventory[4],
			player->inventory[5], player->inventory[6]);
			dprintf(net->fd_graphic, "bct %d %d %d %d %d %d %d %d %d\n",
			player->x, player->y, e->map[player->y][player->x][0],
			e->map[player->y][player->x][1], e->map[player->y][player->x][2],
			e->map[player->y][player->x][3], e->map[player->y][player->x][4],
			e->map[player->y][player->x][5], e->map[player->y][player->x][6]);
			ft_lstadd_or_create(e, "ok\n", player->id, 7 / e->time);
		}
		else
			ft_lstadd_or_create(e, "ko\n", player->id, 7 / e->time);
	}
}

void				put(t_player *player, t_env *e, t_net *net)
{
	int		c;

	if (ft_strncmp(net->fds[player->id].buf_read, "pose", 4) == 0)
	{
		c = inv_selection(ft_strsplit(net->fds[player->id].buf_read, ' ')[1]);
		if (c != -1 && player->inventory[c] != 0)
		{
			player->inventory[c] -= 1;
			e->map[player->y][player->x][c] += 1;
			dprintf(net->fd_graphic, "pdr #%d %d\n", player->id, c);
			dprintf(net->fd_graphic, "pin #%d %d %d %d %d %d %d %d %d %d\n",
			player->id, player->x, player->y, player->inventory[0],
			player->inventory[1], player->inventory[2], player->inventory[3],
			player->inventory[4], player->inventory[5], player->inventory[6]);
			dprintf(net->fd_graphic, "bct %d %d %d %d %d %d %d %d %d\n",
			player->x, player->y, e->map[player->y][player->x][0],
			e->map[player->y][player->x][1], e->map[player->y][player->x][2],
			e->map[player->y][player->x][3], e->map[player->y][player->x][4],
			e->map[player->y][player->x][5], e->map[player->y][player->x][6]);
			ft_lstadd_or_create(e, "ok\n", player->id, 7 / e->time);
		}
		else
			ft_lstadd_or_create(e, "ko\n", player->id, 7 / e->time);
	}
}
