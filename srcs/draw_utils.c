/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 16:28:40 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:03:27 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>
#include <mlx.h>

void			debug(t_color *col, t_object *object)
{
	if (object)
	{
		col->r = object->material.color.r;
		col->g = object->material.color.g;
		col->b = object->material.color.b;
	}
	else
	{
		col->r = 0;
		col->g = 0;
		col->b = 0;
	}
}

void			init_ray(t_env *e, t_ray *ray)
{
	ray->origin = e->camera.position;
	ray->vector = vectorize(ray->origin, e->view);
	ray->vector.x += e->pos.x;
	ray->vector.y += e->pos.y;
	*ray = transf_ray(*ray, transf_matrix(e->camera.rotation,
				e->camera.position));
	ray->vector = normalize(ray->vector);
}

void			init_view(t_env *e)
{
	e->view.x = e->camera.position.x - (WIN_WIDTH / 2);
	e->view.y = e->camera.position.y - (WIN_HEIGHT / 2);
	e->view.z = (WIN_WIDTH) / (2 * tan(((M_PI / 180) * FOV) / 2));
}

double			check_min(double delta, double a, double b, double c)
{
	double		t1;
	double		t2;

	if (a == 0)
		return ((-1) * (c / b));
	if (delta < 0)
		return (0);
	t1 = (((-1) * b) + sqrt(delta)) / (2 * a);
	t2 = (((-1) * b) - sqrt(delta)) / (2 * a);
	if (t1 < 0 && t2 < 0)
		return (t1 < t2 ? t1 : t2);
	else if (t1 < 0)
		return (t2);
	else if (t2 < 0)
		return (t1);
	else
	{
		if (t1 > 0.01 && t2 > 0.01)
			return (t1 < t2 ? t1 : t2);
		else if (t1 < t2)
			return (t2);
		else
			return (t1);
	}
}

double			get_max(double delta, double a, double b, double c)
{
	double		t1;
	double		t2;
	double		t;

	if (a == 0)
		return ((-1) * (c / b));
	if (delta >= 0)
	{
		t1 = (((-1) * b) + sqrt(delta)) / (2 * a);
		t2 = (((-1) * b) - sqrt(delta)) / (2 * a);
		if (t1 < 0)
			return (t2);
		else if (t2 < 0)
			return (t1);
		else
			t = (t1 > t2 ? t1 : t2);
		return (t);
	}
	return (0);
}
