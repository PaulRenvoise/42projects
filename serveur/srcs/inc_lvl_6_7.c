/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc_lvl_6_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 12:20:53 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/12 12:22:20 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>

int		incantation_lvl_6(t_env *e, int x, int y)
{
	e->map[y][x][1] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][1] += 1;
	e->map[y][x][2] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][2] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][2] += 1;
	e->map[y][x][3] -= 3;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	e->map[y][x][5] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][5] += 1;
	return (1);
}

int		incantation_lvl_7(t_env *e, int x, int y)
{
	e->map[y][x][1] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][1] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][1] += 1;
	e->map[y][x][2] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][2] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][2] += 1;
	e->map[y][x][3] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	e->map[y][x][4] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][4] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][4] += 1;
	e->map[y][x][5] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][5] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][5] += 1;
	e->map[y][x][6] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][6] += 1;
	return (1);
}
