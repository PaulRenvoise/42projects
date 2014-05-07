/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 12:51:06 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 22:13:16 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <mlx.h>
#include <stdlib.h>

void		mlx_put_pixel_to_image(t_env *e, int x, int y, t_color *c)
{
	if (e->img.endian)
	{
		e->img.data[y * e->img.sizeline + x
			* e->img.bpp / 8] = mlx_get_color_value(e->mlx_info.mlx, c->r);
		e->img.data[y * e->img.sizeline + x
			* e->img.bpp / 8 + 1] = mlx_get_color_value(e->mlx_info.mlx, c->g);
		e->img.data[y * e->img.sizeline + x
			* e->img.bpp / 8 + 2] = mlx_get_color_value(e->mlx_info.mlx, c->b);
	}
	else
	{
		e->img.data[y * e->img.sizeline + x
			* e->img.bpp / 8] = mlx_get_color_value(e->mlx_info.mlx, c->b);
		e->img.data[y * e->img.sizeline + x
			* e->img.bpp / 8 + 1] = mlx_get_color_value(e->mlx_info.mlx, c->g);
		e->img.data[y * e->img.sizeline + x
			* e->img.bpp / 8 + 2] = mlx_get_color_value(e->mlx_info.mlx, c->r);
	}
}

static void	init_img(t_env *e)
{
	int		bpp;
	int		sizeline;
	int		endian;

	e->img.data = mlx_get_data_addr(e->img.ptr, &bpp, &sizeline, &endian);
	e->img.sizeline = sizeline;
	e->img.bpp = bpp;
	e->img.endian = endian;
}

static int	expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx_info.mlx, e->mlx_info.win, e->img.ptr, 0, 0);
	return (0);
}

static int	key_hook(int keycode, t_env *e)
{
	(void)e;
	if (keycode == 65307)
		exit(0);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	*e;

	e = (t_env *)malloc(sizeof(t_env));
	e->debug = 0;
	e->objects = NULL;
	e->lights = NULL;
	init_parser(e, ac, av);
	if ((e->mlx_info.mlx = mlx_init()) == NULL)
		exit(0);
	e->mlx_info.win = mlx_new_window(e->mlx_info.mlx,
					WIN_WIDTH, WIN_HEIGHT, av[1]);
	e->img.ptr = mlx_new_image(e->mlx_info.mlx, WIN_WIDTH, WIN_HEIGHT);
	init_img(e);
	draw(e);
	mlx_expose_hook(e->mlx_info.win, expose_hook, e);
	mlx_key_hook(e->mlx_info.win, key_hook, e);
	mlx_loop(e->mlx_info.mlx);
	return (0);
}
