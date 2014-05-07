/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 12:39:51 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 18:35:44 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>
#include <stdlib.h>

void	phong_lights(t_env *e, t_vlight *vl, t_coord inter, t_coord normal)
{
	int		i;
	t_ray	spot;
	t_list	*head;

	i = 0;
	head = e->lights;
	while (e->lights)
	{
		spot.vector = normalize(vectorize(inter,
					((t_light *)(e->lights->content))->position));
		spot.origin = ((t_light *)(e->lights->content))->position;
		if (vl->object)
		{
			ambiant(vl->col, vl->old, vl->object);
			diffuse(vl->col, vl->old, vl->object, dot_product(spot.vector,
					normal));
			specular(vl, spot, normal);
		}
		i++;
		e->lights = e->lights->next;
	}
	vl->col->r /= i;
	vl->col->g /= i;
	vl->col->b /= i;
	e->lights = head;
}

void	calc_shadows(t_env *e, t_color *col, t_list *objects, t_coord inter)
{
	double	coef;
	t_list	*head;

	head = e->lights;
	while (e->lights)
	{
		e->spot.vector = normalize(vectorize(inter,
					((t_light *)(e->lights->content))->position));
		e->spot.origin = ((t_light *)(e->lights->content))->position;
		if ((coef = shadows(e, objects, inter)))
		{
			col->r /= (coef);
			col->g /= (coef);
			col->b /= (coef);
		}
		e->lights = e->lights->next;
	}
	e->lights = head;
}

void	direct_light(t_env *e, t_color *col, t_ray ray_save, t_list *head)
{
	t_ray	camspot;
	double	dirlight;
	double	angle;

	while (e->lights)
	{
		camspot.origin = ray_save.origin;
		camspot.vector = normalize(vectorize(ray_save.origin,
					((t_light *)(e->lights->content))->position));
		angle = (180 * acos(dot_product(ray_save.vector,
						camspot.vector)) / M_PI);
		if (angle)
		{
			dirlight = 1 / (fabs((ray_save.origin.z / 2)
						- ((t_light *)(e->lights->content))->position.z));
			dirlight /= 0.00125 * angle;
			col->r += 255 * (dirlight);
			col->g += 255 * (dirlight);
			col->b += 255 * (dirlight);
		}
		e->lights = e->lights->next;
	}
	e->lights = head;
}

void	light(t_env *e, t_color *col, t_coord inter, t_reftrans rt)
{
	t_coord		normal;
	t_list		*head;
	t_vlight	vl;
	t_coord		old_inter;
	double		*matrix;

	vl.old = *col;
	vl.col = col;
	col->r = 0;
	col->g = 0;
	col->b = 0;
	head = e->lights;
	vl.object = rt.object;
	old_inter = inter;
	if (rt.object)
	{
		matrix = get_matrix(rt.object);
		inter = transf_point(inter, matrix);
		calculate_normal(e, &normal, rt.object, old_inter);
	}
	phong_lights(e, &vl, inter, normal);
	if (rt.object)
		calc_shadows(e, col, e->objects, inter);
	direct_light(e, col, rt.ray_save, head);
	adjust_color(col);
}
