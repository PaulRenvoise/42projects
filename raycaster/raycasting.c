/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 13:50:46 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/19 18:47:47 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <math.h>
#include <mlx.h>

static void		define_walldist(t_env *e)
{
	if (!e->v.side)
		e->v.pwalldist = fabs((e->v.mapx - e->v.rayx + (1 - e->v.stepx) / 2)
								/ e->v.raydirx);
	else
		e->v.pwalldist = fabs((e->v.mapy - e->v.rayy + (1 - e->v.stepy) / 2)
								/ e->v.raydiry);
	if (e->v.pwalldist < 0.05)
		e->v.pwalldist = 0.05;
}

static void		wall_hit(t_env *e)
{
	int			wall;

	wall = 0;
	while (!wall)
	{
		if (e->v.sidedistx < e->v.sidedisty)
		{
			e->v.sidedistx += e->v.ddistx;
			e->v.mapx += e->v.stepx;
			e->v.side = 0;
		}
		else
		{
			e->v.sidedisty += e->v.ddisty;
			e->v.mapy += e->v.stepy;
			e->v.side = 1;
		}
		if (e->map[e->v.mapx][e->v.mapy] > 0)
			wall = 1;
	}
}

static void		define_side_n_step(t_env *e)
{
	if (e->v.raydirx < 0)
	{
		e->v.stepx = -1;
		e->v.sidedistx = (e->v.rayx - e->v.mapx) * e->v.ddistx;
	}
	else
	{
		e->v.stepx = 1;
		e->v.sidedistx = (e->v.mapx + 1.0 - e->v.rayx) * e->v.ddistx;
	}
	if (e->v.raydiry < 0)
	{
		e->v.stepy = -1;
		e->v.sidedisty = (e->v.rayy - e->v.mapy) * e->v.ddisty;
	}
	else
	{
		e->v.stepy = 1;
		e->v.sidedisty = (e->v.mapy + 1.0 - e->v.rayy) * e->v.ddisty;
	}
}

static void		compute_vars(int x, t_env *e)
{
	e->v.camx = ((2 * x) / (double)WW) - 1;
	e->v.rayx = e->v.posx;
	e->v.rayy = e->v.posy;
	e->v.raydirx = e->v.dirx + e->v.spanx * e->v.camx;
	e->v.raydiry = e->v.diry + e->v.spany * e->v.camx;
	e->v.mapx = (int)e->v.rayx;
	e->v.mapy = (int)e->v.rayy;
	e->v.ddistx = sqrt(1 + (e->v.raydiry * e->v.raydiry)
						/ (e->v.raydirx * e->v.raydirx));
	e->v.ddisty = sqrt(1 + (e->v.raydirx * e->v.raydirx)
						/ (e->v.raydiry * e->v.raydiry));
}

void			raycasting(int x, t_env *e)
{
	check_inputs(e);
	check_triggers(e);
	while (x < WW)
	{
		compute_vars(x, e);
		define_side_n_step(e);
		wall_hit(e);
		if (e->m.space && (e->map[e->v.mapx][e->v.mapy] == 7
						|| e->map[e->v.mapx][e->v.mapy] == 8) && x == (WW / 2))
		{
			e->map[e->v.mapx][e->v.mapy] = 0;
			e->m.space = 0;
			e->misc.action++;
		}
		define_walldist(e);
		draw_img(x, e);
		x++;
		if ((1 / (e->fps.fps / 1000)) > 29)
			mlx_string_put(e->mlx, e->win, WW - 20, 20, 0x00BB00,
							ft_itoa((int)(1 / (e->fps.fps / 1000))));
		else
			mlx_string_put(e->mlx, e->win, WW - 20, 20, 0xFF0000,
							ft_itoa((int)(1 / (e->fps.fps / 1000))));
	}
}
