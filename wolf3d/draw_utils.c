/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 14:20:42 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/19 18:47:17 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <mlx.h>

static void		mlx_put_pixel_to_image(int x, int y, t_env *e)
{
	if (!e->i.endian)
	{
		e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize)]
			= (char)mlx_get_color_value(e->mlx, e->c.wb);
		e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize) + 1]
			= (char)mlx_get_color_value(e->mlx, e->c.wg);
		e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize) + 2]
			= (char)mlx_get_color_value(e->mlx, e->c.wr);
	}
	else
	{
		e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize)]
			= (char)mlx_get_color_value(e->mlx, e->c.wr);
		e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize) + 1]
			= (char)mlx_get_color_value(e->mlx, e->c.wg);
		e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize) + 2]
			= (char)mlx_get_color_value(e->mlx, e->c.wb);
	}
}

static void		select_texture3(t_env *e)
{
	if (e->map[e->v.mapx][e->v.mapy] == 12)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texportal,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	else if (e->map[e->v.mapx][e->v.mapy] == 13)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texanti,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	else if (e->map[e->v.mapx][e->v.mapy] == 14)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texstanley,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	else if (e->map[e->v.mapx][e->v.mapy] == 15)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texqube,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
}

static void		select_texture2(int x, t_env *e)
{
	if (e->map[e->v.mapx][e->v.mapy] == 9)
	{
		while (e->tw.stripestart < e->tw.stripeend)
			mlx_put_pixel_to_image(x, e->tw.stripestart++, e);
	}
	else if (e->map[e->v.mapx][e->v.mapy] == 10)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texend,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	else if (e->map[e->v.mapx][e->v.mapy] == 11)
	{
		if (!e->v.side)
		{
			if (e->v.stepx < 0)
				mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.tex,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
			else
				mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texdoor,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
		}
		else
			mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texdoor,
						&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	}
	select_texture3(e);
}

void			select_texture(int x, t_env *e)
{
	if (e->map[e->v.mapx][e->v.mapy] == 1)
	{
		if (e->v.stepy > 0)
			mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texscrt,
								&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
		else
			mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.tex,
								&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	}
	if (e->map[e->v.mapx][e->v.mapy] == 4)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texarrow,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	else if (e->map[e->v.mapx][e->v.mapy] == 5)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texintro,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	else if (e->map[e->v.mapx][e->v.mapy] == 6)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texkeys,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	else if (e->map[e->v.mapx][e->v.mapy] == 7)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.texblock,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	else if (e->map[e->v.mapx][e->v.mapy] == 8)
		mlx_check((void*)(e->tw.data = mlx_get_data_addr(e->tw.textip,
							&e->tw.bpp, &e->tw.lsize, &e->tw.endian)));
	select_texture2(x, e);
}

void			floorcasting(t_env *e)
{
	if (!e->v.side && e->v.raydirx > 0)
	{
		e->f.floorx = e->v.mapx;
		e->f.floory = e->v.mapy + e->v.wallx;
	}
	else if (!e->v.side && e->v.raydirx < 0)
	{
		e->f.floorx = e->v.mapx + 1.0;
		e->f.floory = e->v.mapy + e->v.wallx;
	}
	else if (e->v.side && e->v.raydiry > 0)
	{
		e->f.floorx = e->v.mapx + e->v.wallx;
		e->f.floory = e->v.mapy;
	}
	else
	{
		e->f.floorx = e->v.mapx + e->v.wallx;
		e->f.floory = e->v.mapy + 1.0;
	}
	e->f.walldist = e->v.pwalldist;
	e->f.camdist = 0.0;
}
