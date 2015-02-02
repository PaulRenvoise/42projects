/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 11:52:10 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/13 11:39:32 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

static void		check_tile(t_env *e, char *msg, int x, int y)
{
	int	k;

	if ((k = e->map[y][x][0]) != 0)
		while (k-- > 0)
			ft_strcat(msg, " nourriture");
	if ((k = e->map[y][x][1]) != 0)
		while (k-- > 0)
			ft_strcat(msg, " linemate");
	if ((k = e->map[y][x][2]) != 0)
		while (k-- > 0)
			ft_strcat(msg, " deraumere");
	if ((k = e->map[y][x][3]) != 0)
		while (k-- > 0)
			ft_strcat(msg, " sibur");
	if ((k = e->map[y][x][4]) != 0)
		while (k-- > 0)
			ft_strcat(msg, " mendiane");
	if ((k = e->map[y][x][5]) != 0)
		while (k-- > 0)
			ft_strcat(msg, " phiras");
	if ((k = e->map[y][x][6]) != 0)
		while (k-- > 0)
			ft_strcat(msg, " thystame");
}

static void		inc_var(t_player *player, int *x, int *y)
{
	if (player->orientation == NORD)
		(*x)++;
	else if (player->orientation == EST)
		(*y)--;
	else if (player->orientation == SUD)
		(*x)--;
	else
		(*y)++;
}

void			compute_rows(t_env *e, t_player *player, char *msg, int i)
{
	int		x;
	int		y;
	int		j;
	int		k;

	init_pos(player, &x, &y, i);
	j = 0;
	while (j < ((i * 2) + 1))
	{
		correct_pos(e, &x, &y);
		check_tile(e, msg, x, y);
		if ((k = get_player_pos_voir(e->teams, x, y, player->id)) != 0)
			while (k-- > 0)
				ft_strcat(msg, " joueur");
		ft_strcat(msg, ",");
		inc_var(player, &x, &y);
		j++;
	}
}

void			see(t_player *player, t_env *e, t_net *net)
{
	int		i;
	char	msg[BUF_SIZE + 1];

	ft_bzero(msg, BUF_SIZE + 1);
	if (ft_strcmp(net->fds[player->id].buf_read, "voir\n") == 0)
	{
		i = 0;
		ft_strcpy(msg, "{");
		while (i <= player->level && i <= e->width && i <= e->height)
		{
			compute_rows(e, player, msg, i);
			i++;
		}
		ft_strcat(msg, " }\n");
		ft_lstadd_or_create(e, msg, player->id, 7 / e->time);
	}
}
