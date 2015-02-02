/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 16:19:21 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 20:23:26 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

static double	test_t(double t1, double t2)
{
	if (t1 && t2)
	{
		if (t1 < t2)
			return (t1);
		else
			return (t2);
	}
	else
	{
		if (t1)
			return (t1);
		else
			return (t2);
	}
}

double			caps_cone(t_cone *cone, t_ray ray, double min, double max)
{
	t_coord		inter;
	double		y1;
	double		y2;
	double		t1;
	double		t2;

	t1 = 0;
	t2 = 0;
	inter = pt_inter(ray, min);
	y1 = inter.y;
	inter = pt_inter(ray, max);
	y2 = inter.y;
	if (y1 > -cone->height && y1 < cone->height)
		t1 = min;
	if (y2 > -cone->height && y2 < cone->height)
		t2 = max;
	if (cone->caps && (y2 < cone->height && y1 > cone->height))
		return ((cone->height - ray.origin.y) / ray.vector.y);
	if (cone->caps && ((y1 < -cone->height && y2 > -cone->height)))
		return ((-cone->height - ray.origin.y) / ray.vector.y);
	return (test_t(t1, t2));
}

double			caps_cylinder(t_cylinder *cylinder, t_ray ray, double min,
				double max)
{
	t_coord		inter;
	double		y1;
	double		y2;
	double		t1;
	double		t2;

	t1 = 0;
	t2 = 0;
	inter = pt_inter(ray, min);
	y1 = inter.y;
	inter = pt_inter(ray, max);
	y2 = inter.y;
	if (y1 > -cylinder->height && y1 < cylinder->height)
		t1 = min;
	if (y2 > -cylinder->height && y2 < cylinder->height)
		t2 = max;
	if (cylinder->caps && (y2 < cylinder->height && y1 > cylinder->height))
		return ((cylinder->height - ray.origin.y) / ray.vector.y);
	if (cylinder->caps && ((y1 < -cylinder->height && y2 > -cylinder->height)))
		return ((-cylinder->height - ray.origin.y) / ray.vector.y);
	return (test_t(t1, t2));
}

double			caps_sphere(t_sphere *sphere, t_ray ray, double min,
				double max)
{
	t_coord		inter;
	double		y1;
	double		y2;
	double		t1;
	double		t2;

	t1 = 0;
	t2 = 0;
	inter = pt_inter(ray, min);
	y1 = inter.y;
	inter = pt_inter(ray, max);
	y2 = inter.y;
	if (y1 > -sphere->height)
		t1 = min;
	if (y2 > -sphere->height)
		t2 = max;
	if (sphere->caps && ((y1 < -sphere->height && y2 > -sphere->height)))
		return ((-sphere->height - ray.origin.y) / ray.vector.y);
	return (test_t(t1, t2));
}
