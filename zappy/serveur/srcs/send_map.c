/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 11:53:45 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/16 15:51:20 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

static void	send_tile(t_env *e, int i, int j, int cs)
{
	dprintf(cs, "bct %d %d %d %d %d %d %d %d %d\n", j, i,
			e->map[i][j][0], e->map[i][j][1], e->map[i][j][2],
			e->map[i][j][3], e->map[i][j][4], e->map[i][j][5], e->map[i][j][6]);
}

static void	send_tile_delay(t_env *e, char *msg, int i, int j)
{
	sprintf(msg + ft_strlen(msg), "bct %d %d %d %d %d %d %d %d %d\n", j, i,
			e->map[i][j][0], e->map[i][j][1], e->map[i][j][2],
			e->map[i][j][3], e->map[i][j][4], e->map[i][j][5], e->map[i][j][6]);
}

void		send_map(t_env *e, int cs, float delay)
{
	int		i;
	int		j;
	char	msg[BUF_SIZE + 1];

	i = 0;
	ft_bzero(msg, BUF_SIZE + 1);
	while (i < e->height)
	{
		j = 0;
		while (j < e->width)
		{
			if (delay == 0)
				send_tile(e, i, j, cs);
			else
				send_tile_delay(e, msg, i, j);
			j++;
		}
		i++;
	}
	if (delay != 0)
	{
		ft_lstadd_or_create(e, msg, cs, delay / e->time);
	}
}
