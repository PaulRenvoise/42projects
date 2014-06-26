/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 17:36:47 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/12 14:24:51 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

void		init_pos(t_player *player, int *x, int *y, int i)
{
	*x = player->x - i;
	*y = player->y - i;
	if (player->orientation == NORD)
		*y = player->y + i;
	if (player->orientation == EST)
	{
		*x = player->x + i;
		*y = player->y + i;
	}
	if (player->orientation == SUD)
		*x = player->x + i;
}

void		correct_pos(t_env *e, int *x, int *y)
{
	if (*x >= e->width)
		*x = 0;
	if (*y < 0)
		*y = e->height - 1;
	if (*x < 0)
		*x = e->width - 1;
	if (*y >= e->height)
		*y = 0;
}
