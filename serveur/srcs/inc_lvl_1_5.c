/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc_lvl_1_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 12:20:37 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/12 12:21:36 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>

int		incantation_lvl_1(t_env *e, int x, int y)
{
	e->map[y][x][1] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][1] += 1;
	return (1);
}

int		incantation_lvl_2(t_env *e, int x, int y)
{
	e->map[y][x][1] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][1] += 1;
	e->map[y][x][2] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][2] += 1;
	e->map[y][x][3] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	return (1);
}

int		incantation_lvl_3(t_env *e, int x, int y)
{
	e->map[y][x][1] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][1] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][1] += 1;
	e->map[y][x][3] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	e->map[y][x][5] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][5] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][5] += 1;
	return (1);
}

int		incantation_lvl_4(t_env *e, int x, int y)
{
	e->map[y][x][1] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][1] += 1;
	e->map[y][x][2] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][2] += 1;
	e->map[y][x][3] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	e->map[y][x][5] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][5] += 1;
	return (1);
}

int		incantation_lvl_5(t_env *e, int x, int y)
{
	e->map[y][x][1] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][1] += 1;
	e->map[y][x][2] -= 2;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][2] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][2] += 1;
	e->map[y][x][3] -= 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][3] += 1;
	e->map[y][x][4] -= 3;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][4] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][4] += 1;
	e->map[random_in_range(0, e->width)][random_in_range(0, e->height)][4] += 1;
	return (1);
}
