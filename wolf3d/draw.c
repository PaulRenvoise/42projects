/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 12:35:27 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/19 18:47:16 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

static void		mlx_put_texfloor_to_image(int x, int y, t_env *e)
{
	e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize)]
		= e->tf.data[(e->tf.texx * (e->tf.bpp / 8))
					+ (e->tf.texy * e->tf.lsize)];
	e->i.data[(x * (e->i.bpp / 8)) + ((WH - y) * e->i.lsize)]
		= e->tf.data[(e->tf.texx * (e->tf.bpp / 8))
					+ (e->tf.texy * e->tf.lsize)];
	e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize) + 1]
		= e->tf.data[(e->tf.texx * (e->tf.bpp / 8))
					+ (e->tf.texy * e->tf.lsize) + 1];
	e->i.data[(x * (e->i.bpp / 8)) + ((WH - y) * e->i.lsize) + 1]
		= e->tf.data[(e->tf.texx * (e->tf.bpp / 8))
					+ (e->tf.texy * e->tf.lsize) + 1];
	e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize) + 2]
		= e->tf.data[(e->tf.texx * (e->tf.bpp / 8))
					+ (e->tf.texy * e->tf.lsize) + 2];
	e->i.data[(x * (e->i.bpp / 8)) + ((WH - y) * e->i.lsize) + 2]
		= e->tf.data[(e->tf.texx * (e->tf.bpp / 8))
					+ (e->tf.texy * e->tf.lsize) + 2];
}

static void		mlx_put_texwall_to_image(int x, int y, t_env *e)
{
	mlx_check((e->tw.data = mlx_get_data_addr(e->tw.tex, &e->tw.bpp,
			&e->tw.lsize, &e->tw.endian)));
	select_texture(x, e);
	e->tw.texy = abs(e->tw.texy);
	e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize)]
		= e->tw.data[(e->tw.texx * (e->tw.bpp / 8))
					+ (e->tw.texy * e->tw.lsize)];
	e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize) + 1]
		= e->tw.data[(e->tw.texx * (e->tw.bpp / 8))
					+ (e->tw.texy * e->tw.lsize) + 1];
	e->i.data[(x * (e->i.bpp / 8)) + (y * e->i.lsize) + 2]
		= e->tw.data[(e->tw.texx * (e->tw.bpp / 8))
					+ (e->tw.texy * e->tw.lsize) + 2];
}

static void		draw_floor(int x, t_env *e)
{
	floorcasting(e);
	while (e->tw.stripeend < WH)
	{
		e->f.dist = WH / (2.0 * e->tw.stripeend - WH);
		e->f.weight = (e->f.dist - e->f.camdist)
					/ (e->f.walldist - e->f.camdist);
		e->f.curx = e->f.weight * e->f.floorx + (1.0 - e->f.weight) * e->v.posx;
		e->f.cury = e->f.weight * e->f.floory + (1.0 - e->f.weight) * e->v.posy;
		e->tf.texx = (int)(e->f.curx * e->tf.w) % e->tf.w;
		e->tf.texy = (int)(e->f.cury * e->tf.h) % e->tf.h;
		mlx_put_texfloor_to_image(x, e->tw.stripeend, e);
		e->tw.stripeend++;
	}
}

static void		draw_wall(int x, t_env *e)
{
	e->tw.texx = (int)(e->v.wallx * (double)(e->tw.w));
	if (!e->v.side && e->v.raydirx > 0)
		e->tw.texx = e->tw.w - e->tw.texx - 1;
	if (e->v.side && e->v.raydiry < 0)
		e->tw.texx = e->tw.w - e->tw.texx - 1;
	while (e->tw.stripestart < e->tw.stripeend)
	{
		e->tw.d = (e->tw.stripestart * 256) - (WH * 128)
				+ (e->tw.stripeheight * 128);
		e->tw.texy = ((e->tw.d * e->tw.h) / e->tw.stripeheight) / 256;
		mlx_put_texwall_to_image(x, e->tw.stripestart, e);
		e->tw.stripestart++;
	}
}

void			draw_img(int x, t_env *e)
{
	if (e->v.side)
		e->v.wallx = e->v.rayx +
					((e->v.mapy - e->v.rayy +
					(1 - e->v.stepy) / 2) / e->v.raydiry) * e->v.raydirx;
	else
		e->v.wallx = e->v.rayy +
					((e->v.mapx - e->v.rayx +
					(1 - e->v.stepx) / 2) / e->v.raydirx) * e->v.raydiry;
	e->v.wallx -= floor(e->v.wallx);
	e->tw.stripeheight = abs((int)(WH / e->v.pwalldist));
	if ((e->tw.stripestart = (-(e->tw.stripeheight) / 2) + (WH / 2)) < 0)
		e->tw.stripestart = 0;
	if ((e->tw.stripeend = (e->tw.stripeheight / 2) + (WH / 2)) >= WH)
		e->tw.stripeend = WH - 1;
	mlx_check((e->i.data = mlx_get_data_addr(e->i.img, &e->i.bpp,
			&e->i.lsize, &e->i.endian)));
	mlx_check((e->tf.data = mlx_get_data_addr(e->tf.tex, &e->tf.bpp,
			&e->tf.lsize, &e->tf.endian)));
	draw_wall(x, e);
	draw_floor(x, e);
}
