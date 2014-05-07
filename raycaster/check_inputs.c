/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 12:25:38 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/19 18:47:18 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <math.h>
#include <stdlib.h>

static void		check_sprint_reset(t_env *e)
{
	int			i;

	if (e->m.sprint)
	{
		e->m.speed += 0.04;
		e->m.rot += 0.03;
	}
	if (e->m.reset)
	{
		i = 0;
		init_var_n_inputs(e);
		while (i <= 22)
		{
			free(e->map[i]);
			e->map[i] = NULL;
			i++;
		}
		free(e->map);
		stock_map(e);
		e->misc.reset++;
		e->m.reset = 0;
	}
}

static void		check_up_down(t_env *e)
{
	double		tmpx;
	double		tmpy;

	tmpx = e->v.dirx * e->m.speed;
	tmpy = e->v.diry * e->m.speed;
	if (e->m.up)
	{
		if (e->map[(int)(e->v.posx + tmpx)][(int)e->v.posy] < 2)
			e->v.posx += e->v.dirx * e->m.speed;
		if (e->map[(int)e->v.posx][(int)(e->v.posy + tmpy)] < 2)
			e->v.posy += e->v.diry * e->m.speed;
	}
	if (e->m.down)
	{
		e->m.speed -= 0.03;
		if (e->map[(int)(e->v.posx - tmpx)][(int)e->v.posy] < 2)
			e->v.posx -= e->v.dirx * e->m.speed;
		if (e->map[(int)e->v.posx][(int)(e->v.posy - tmpy)] < 2)
			e->v.posy -= e->v.diry * e->m.speed;
	}
}

static void		check_right_left(t_env *e)
{
	if (e->m.right)
	{
		e->v.odirx = e->v.dirx;
		e->v.dirx = e->v.dirx * cos(-e->m.rot) - e->v.diry * sin(-e->m.rot);
		e->v.diry = e->v.odirx * sin(-e->m.rot) + e->v.diry * cos(-e->m.rot);
		e->v.ospanx = e->v.spanx;
		e->v.spanx = e->v.spanx * cos(-e->m.rot) - e->v.spany * sin(-e->m.rot);
		e->v.spany = e->v.ospanx * sin(-e->m.rot) + e->v.spany * cos(-e->m.rot);
	}
	if (e->m.left)
	{
		e->v.odirx = e->v.dirx;
		e->v.dirx = e->v.dirx * cos(e->m.rot) - e->v.diry * sin(e->m.rot);
		e->v.diry = e->v.odirx * sin(e->m.rot) + e->v.diry * cos(e->m.rot);
		e->v.ospanx = e->v.spanx;
		e->v.spanx = e->v.spanx * cos(e->m.rot) - e->v.spany * sin(e->m.rot);
		e->v.spany = e->v.ospanx * sin(e->m.rot) + e->v.spany * cos(e->m.rot);
	}
}

void			check_inputs(t_env *e)
{
	e->m.speed = e->fps.fps * 0.003;
	e->m.rot = e->fps.fps * 0.002;
	check_sprint_reset(e);
	check_up_down(e);
	check_right_left(e);
}
