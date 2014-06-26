/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 12:25:16 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:15:24 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>
#include <sys/socket.h>

int			required_incantation(t_env *e, int x, int y, int lvl)
{
	if (lvl == 1 && e->map[y][x][1] >= 1)
		return (incantation_lvl_1(e, x, y));
	else if (lvl == 2 && e->map[y][x][1] >= 1 && e->map[y][x][2] >= 1
		&& e->map[y][x][3] >= 1 && get_numb_player_at(e->teams, x, y, lvl) >= 2)
		return (incantation_lvl_2(e, x, y));
	else if (lvl == 3 && e->map[y][x][1] >= 2 && e->map[y][x][3] >= 1
		&& e->map[y][x][5] >= 2 && get_numb_player_at(e->teams, x, y, lvl) >= 2)
		return (incantation_lvl_3(e, x, y));
	else if (lvl == 4 && e->map[y][x][1] >= 1 && e->map[y][x][2] >= 1
		&& e->map[y][x][3] >= 2 && e->map[y][x][5] >= 1
		&& get_numb_player_at(e->teams, x, y, lvl) >= 4)
		return (incantation_lvl_4(e, x, y));
	else if (lvl == 5 && e->map[y][x][1] >= 1 && e->map[y][x][2] >= 2
		&& e->map[y][x][3] >= 1 && e->map[y][x][4] >= 3
		&& get_numb_player_at(e->teams, x, y, lvl) >= 4)
		return (incantation_lvl_5(e, x, y));
	else if (lvl == 6 && e->map[y][x][1] >= 1 && e->map[y][x][2] >= 2
		&& e->map[y][x][3] >= 3 && e->map[y][x][5] >= 1
		&& get_numb_player_at(e->teams, x, y, lvl) >= 6)
		return (incantation_lvl_6(e, x, y));
	else if (lvl == 7 && e->map[y][x][1] >= 2 && e->map[y][x][2] >= 2
		&& e->map[y][x][3] >= 2 && e->map[y][x][4] >= 2 && e->map[y][x][5] >= 2
		&& e->map[y][x][6] >= 1 && get_numb_player_at(e->teams, x, y, lvl) >= 6)
		return (incantation_lvl_7(e, x, y));
	return (0);
}

t_team		*check_if_win(t_env *e)
{
	t_list	*head;
	t_list	*players;
	int		i;

	head = e->teams;
	while (e->teams)
	{
		players = ((t_team *)(e->teams->content))->players;
		i = 0;
		while (players)
		{
			if (((t_player *)players->content)->level == 8)
				i++;
			players = players->next;
		}
		if (i == 6)
			return ((t_team *)(e->teams->content));
		e->teams = e->teams->next;
	}
	e->teams = head;
	return (NULL);
}

void		send_to_gfx(t_env *e, t_net *net, t_player *player, t_list *list)
{
	char		msg[BUF_SIZE + 1];
	t_team		*team;

	ft_bzero(msg, BUF_SIZE + 1);
	sprintf(msg, "pie %d %d %d\n", player->x, player->y, 1);
	sprintf(msg + ft_strlen(msg), "plv #%d %d\n", player->id, player->level);
	while (list)
	{
		sprintf(msg + ft_strlen(msg), "plv #%d %d\n", *((int *)(list->content)),
				player->level);
		list = list->next;
	}
	if ((team = check_if_win(e)) != NULL)
		sprintf(msg + ft_strlen(msg), "seg %s\n", team->name);
	ft_lstadd_or_create(e, msg, net->fd_graphic, 300 / e->time);
	ft_lstadd_or_create(e, "sendmap\n", net->fd_graphic, 300 / e->time);
}

t_list		*players_on_tile(t_env *e, t_net *net, t_player *player, char *msg2)
{
	t_player	*player_tile;
	t_list		*list;
	char		msg[BUF_SIZE + 1];

	ft_bzero(msg, BUF_SIZE + 1);
	list = NULL;
	while ((player_tile = get_player_at_pos_level(e->teams, player->x,
					player->y, player->level - 1)) != NULL)
	{
		player_tile->level += 1;
		sprintf(msg2 + ft_strlen(msg2), " #%d", player_tile->id);
		dprintf(player_tile->id, "elevation en cours\n");
		sprintf(msg, "niveau actuel : %d\n", player->level);
		ft_lstadd_or_create(e, msg, player_tile->id, 300 / e->time);
		if (list == NULL)
			list = ft_lstnew(&player_tile->id, sizeof(player_tile->id));
		else
			ft_lstadd_end(&list, ft_lstnew(&player_tile->id,
						sizeof(player_tile->id)));
	}
	sprintf(msg2 + ft_strlen(msg2), "\n");
	send(net->fd_graphic, msg2, ft_strlen(msg2), 0);
	return (list);
}

void		incantation(t_player *player, t_env *e, t_net *net)
{
	char		msg[BUF_SIZE + 1];
	char		msg2[BUF_SIZE + 1];
	t_list		*list;

	ft_bzero(msg, BUF_SIZE + 1);
	ft_bzero(msg2, BUF_SIZE + 1);
	if (ft_strcmp(net->fds[player->id].buf_read, "incantation\n") == 0)
	{
		if (required_incantation(e, player->x, player->y, player->level))
		{
			player->level += 1;
			ft_strcpy(net->fds[player->id].buf_write
					+ ft_strlen(net->fds[player->id].buf_write),
					"elevation en cours\n");
			sprintf(msg, "niveau actuel : %d\n", player->level);
			ft_lstadd_or_create(e, msg, player->id, 300 / e->time);
			sprintf(msg2, "pic %d %d %d #%d", player->x, player->y,
					player->level - 1, player->id);
			list = players_on_tile(e, net, player, msg2);
			send_to_gfx(e, net, player, list);
		}
		else
			sprintf(net->fds[player->id].buf_write
					+ ft_strlen(net->fds[player->id].buf_write), "ko\n");
	}
}
