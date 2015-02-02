/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 15:40:23 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:54:16 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdlib.h>
#include <sys/time.h>

#include <stdio.h>

t_player	*new_player(t_env *e, char *team, t_pos *pos, int cs)
{
	t_player		*player;
	struct timeval	tv;
	float			ftime;

	gettimeofday(&tv, NULL);
	ftime = 126 / e->time;
	player = (t_player *)malloc(sizeof(t_player));
	player->inventory[0] = 10;
	player->inventory[1] = 0;
	player->inventory[2] = 0;
	player->inventory[3] = 0;
	player->inventory[4] = 0;
	player->inventory[5] = 0;
	player->inventory[6] = 0;
	player->time = (1000000 * tv.tv_sec + tv.tv_usec) + (int)(1000000 * ftime);
	player->id = cs;
	player->x = (pos->x == -1 ? random_in_range(0, e->height) : pos->x);
	player->y = (pos->y == -1 ? random_in_range(0, e->width) : pos->y);
	player->orientation = random_in_range(1, 5);
	player->level = 1;
	player->team = (char *)malloc(sizeof(char) * (ft_strlen(team) + 1));
	ft_strcpy(player->team, team);
	return (player);
}

t_team		*new_team(t_env *e, char *name)
{
	t_team	*team;

	team = (t_team *)malloc(sizeof(t_team));
	team->max = e->max_client;
	team->name = (char *)malloc(sizeof(char) * (ft_strlen(name) + 1));
	ft_strcpy(team->name, name);
	team->players = NULL;
	return (team);
}

t_cmd		*new_cmd(char *msg, int fd, unsigned long time)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->msg = (char *)malloc(sizeof(char) * (BUF_SIZE + 1));
	ft_bzero(cmd->msg, BUF_SIZE + 1);
	ft_strcpy(cmd->msg, msg);
	cmd->fd = fd;
	cmd->time = time;
	return (cmd);
}

t_egg		*new_egg(t_env *e, int id, t_player player)
{
	t_egg			*egg;
	struct timeval	tv;
	float			ftime;

	gettimeofday(&tv, NULL);
	ftime = 600 / e->time;
	egg = (t_egg *)malloc(sizeof(t_egg));
	egg->id = id;
	egg->player = player.id;
	egg->x = player.x;
	egg->y = player.y;
	egg->hatched = 0;
	egg->time = (1000000 * tv.tv_sec + tv.tv_usec) + (int)(1000000 * ftime);
	egg->team = (char *)malloc(sizeof(char) * (ft_strlen(player.team) + 1));
	ft_strcpy(egg->team, player.team);
	return (egg);
}
