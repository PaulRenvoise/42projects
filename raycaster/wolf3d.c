/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/31 18:20:49 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/19 18:49:08 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <mlx.h>
#include <X.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int			keypress_hook(int keycode, t_env *e)
{
	if (UP)
		e->m.up = 1;
	else if (DOWN)
		e->m.down = 1;
	else if (LEFT)
		e->m.left = 1;
	else if (RIGHT)
		e->m.right = 1;
	else if (SPRINT)
		e->m.sprint = 1;
	return (0);
}

static int			keyrelease_hook(int keycode, t_env *e)
{
	if (UP)
		e->m.up = 0;
	else if (DOWN)
		e->m.down = 0;
	else if (LEFT)
		e->m.left = 0;
	else if (RIGHT)
		e->m.right = 0;
	else if (SPRINT)
		e->m.sprint = 0;
	else if (RESET)
		e->m.reset = 1;
	else if (SPACE)
		e->m.space = 1;
	else if (ESC)
	{
		kill(g_pidfather, SIGTERM);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static int			loop_hook(t_env *e)
{
	fps(e);
	rand_color(e);
	if (e->i.img)
		mlx_destroy_image(e->mlx, e->i.img);
	mlx_check((e->i.img = mlx_new_image(e->mlx, WW, WH)));
	raycasting(0, e);
	mlx_put_image_to_window(e->mlx, e->win, e->i.img, 0, 0);
	return (0);
}

int					wolf3d(void)
{
	t_env			e;

	stock_map(&e);
	init_var_n_inputs(&e);
	e.misc.reset = 0;
	e.i.img = NULL;
	if (!(e.mlx = mlx_init()))
		return (1);
	init_textures(&e);
	if (!(e.win = mlx_new_window(e.mlx, WW, WH, "THE 42 PARABLE")))
		return (1);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_hook(e.win, KeyPress, KeyPressMask, &keypress_hook, &e);
	mlx_hook(e.win, KeyRelease, KeyReleaseMask, &keyrelease_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}

int					main(void)
{
	extern char		**environ;
	int				pid;
	char			**tab;

	set_music(&tab);
	if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
	else if (!pid)
		wolf3d();
	else
	{
		g_pidfather = getpid();
		execve(tab[0], tab, environ);
	}
	return (0);
}
