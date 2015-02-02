/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbrieuc <rbrieuc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 16:33:58 by rbrieuc           #+#    #+#             */
/*   Updated: 2014/03/27 16:36:27 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

static void		transparency(t_env *e, t_color *col, t_color *col2,
				t_reftrans rt)
{
	double		n;
	double		*matrix;
	t_ray		transparency;
	t_coord		normal;
	t_color		old;

	matrix = get_matrix(rt.object);
	rt.gc.ignore = NULL;
	n = (rt.gc.current ? rt.gc.current->material.refraction
			: 1 / rt.object->material.refraction);
	if (rt.gc.current)
		e->direction = 1;
	calculate_normal(e, &normal, rt.object, pt_inter(rt.ray, rt.t));
	transparency.origin = transf_point(pt_inter(rt.ray, rt.t), (matrix));
	rt.ray = rt.ray_save;
	transparency.vector = calc_transparency(normal, rt.ray.vector,
		fmax(0, sqrt(1 - (pow(n, 2) * (1 - pow(dot_product(normal,
			rt.ray.vector), 2))))), n);
	old = *col;
	if (rt.gc.current)
		rt.gc.current = NULL;
	else
		rt.gc.current = rt.object;
	get_color(e, transparency, col2, rt.gc);
	calc_color(col, col2, old, rt.object->material.transparency);
}

static void		reflection(t_env *e, t_color *col, t_color *col2,
				t_reftrans rt)
{
	t_ray		reflection;
	t_color		old;
	t_coord		normal;

	rt.gc.ignore = rt.object;
	rt.gc.current = NULL;
	if (rt.gc.i < REFLECTION)
	{
		rt.gc.i++;
		calculate_normal(e, &normal, rt.object, pt_inter(rt.ray_tmp, rt.t));
		reflection.origin = transf_point(pt_inter(rt.ray_tmp, rt.t),
				get_matrix(rt.object));
		rt.ray = rt.ray_save;
		reflection.vector = calc_reflection(normal, rt.ray.vector);
		old = *col;
		get_color(e, reflection, col2, rt.gc);
		if (col2->r != -1)
			calc_color(col, col2, old, rt.object->material.reflection);
	}
	else
	{
		col->r = 120;
		col->g = 120;
		col->b = 120;
	}
}

void			get_color(t_env *e, t_ray ray, t_color *col, t_getcolor gc)
{
	t_color		col2;
	t_reftrans	rt;

	rt.ray = ray;
	rt.ray_save = ray;
	rt.gc = gc;
	e->direction = 0;
	rt.object = intersection(e->objects, e, &rt);
	rt.ray_tmp = rt.ray;
	if (rt.object)
		*col = rt.object->material.color;
	else if (!rt.object && gc.ignore != NULL)
	{
		col->r = -1;
		return ;
	}
	if (rt.object && rt.object->material.transparency)
		transparency(e, col, &col2, rt);
	if (rt.object && rt.object->material.reflection)
		reflection(e, col, &col2, rt);
	if (e->lights && !gc.current)
		light(e, col, pt_inter(rt.ray_tmp, rt.t), rt);
	adjust_color(col);
}
