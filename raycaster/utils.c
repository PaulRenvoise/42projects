/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 12:21:26 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/19 18:51:52 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <mlx.h>
#include <stdlib.h>

void			mlx_check(void *data)
{
	if (!data)
		exit(EXIT_FAILURE);
}

void			fps(t_env *e)
{
	e->fps.oldtime = e->fps.now;
	gettimeofday(&e->fps.time, NULL);
	e->fps.usec = e->fps.time.tv_usec;
	e->fps.sec = e->fps.time.tv_sec;
	e->fps.now = ((e->fps.sec * 1000) + (e->fps.usec / 1000.0)) + 0.5;
	e->fps.frametime = (e->fps.now - e->fps.oldtime);
	e->fps.fps = e->fps.frametime;
}

void			init_var_n_inputs(t_env *e)
{
	e->v.posx = 1.7;
	e->v.posy = 3.5;
	e->v.dirx = -1;
	e->v.diry = 0;
	e->v.spanx = 0;
	e->v.spany = 0.66;
	e->m.sprint = 0;
	e->m.up = 0;
	e->m.down = 0;
	e->m.right = 0;
	e->m.left = 0;
	e->m.space = 0;
	e->m.reset = 0;
	e->c.wr = 0;
	e->c.wg = 0;
	e->c.wb = 0;
	e->misc.c = 0;
	e->misc.action = 0;
}

static void		init_textures2(t_env *e)
{
	mlx_check((e->tw.texend = mlx_xpm_file_to_image(e->mlx,
					"./textures/texend.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texarrow = mlx_xpm_file_to_image(e->mlx,
					"./textures/texarrow.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texportal = mlx_xpm_file_to_image(e->mlx,
					"./textures/texportal.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texanti = mlx_xpm_file_to_image(e->mlx,
					"./textures/texanti.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texstanley = mlx_xpm_file_to_image(e->mlx,
					"./textures/texstanley.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texqube = mlx_xpm_file_to_image(e->mlx,
					"./textures/texqube.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tf.tex = mlx_xpm_file_to_image(e->mlx,
					"./textures/texfloor.xpm", &e->tf.w, &e->tf.h)));
}

void			init_textures(t_env *e)
{
	mlx_check((e->tw.tex = mlx_xpm_file_to_image(e->mlx,
					"./textures/texwall.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texdoor = mlx_xpm_file_to_image(e->mlx,
					"./textures/texdoor.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texscrt = mlx_xpm_file_to_image(e->mlx,
					"./textures/texsecret.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texkeys = mlx_xpm_file_to_image(e->mlx,
					"./textures/texkeys.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texintro = mlx_xpm_file_to_image(e->mlx,
					"./textures/texintro.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.texblock = mlx_xpm_file_to_image(e->mlx,
					"./textures/texblock.xpm", &e->tw.w, &e->tw.h)));
	mlx_check((e->tw.textip = mlx_xpm_file_to_image(e->mlx,
					"./textures/textip.xpm", &e->tw.w, &e->tw.h)));
	init_textures2(e);
}
