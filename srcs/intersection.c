/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 16:24:31 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 20:25:46 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

double			intersection_cone(t_env *e, t_cone *cone, t_ray ray)
{
	double	delta;
	double	a;
	double	b;
	double	c;

	(void)e;
	a = pow(ray.vector.x, 2) - (pow(tan(cone->radius * (M_PI / 180)), 2)
			* pow(ray.vector.y, 2)) + pow(ray.vector.z, 2);
	b = 2 * ((ray.vector.x * (ray.origin.x)) - (pow(tan(cone->radius
			* (M_PI / 180)), 2) * (ray.origin.y) * ray.vector.y)
			+ ((ray.origin.z) * ray.vector.z));
	c = pow(ray.origin.x, 2) - (pow(tan(cone->radius * (M_PI / 180)), 2)
			* pow(ray.origin.y, 2)) + pow(ray.origin.z, 2);
	delta = pow(b, 2) - (4 * a * c);
	if (cone->height == 0)
		return (check_min(delta, a, b, c));
	return (caps_cone(cone, ray, check_min(delta, a, b, c),
	get_max(delta, a, b, c)));
}

double			intersection_cylinder(t_env *e, t_cylinder *cylinder, t_ray ray)
{
	double		a;
	double		b;
	double		c;
	double		delta;

	(void)e;
	a = pow(ray.vector.x, 2) + pow(ray.vector.z, 2);
	b = 2 * ((ray.vector.x * (ray.origin.x)) + ((ray.origin.z) * ray.vector.z));
	c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - pow(cylinder->radius, 2);
	delta = pow(b, 2) - (4 * a * c);
	if (cylinder->height == 0)
		return (check_min(delta, a, b, c));
	return (caps_cylinder(cylinder, ray, check_min(delta, a, b, c),
	get_max(delta, a, b, c)));
}

double			intersection_sphere(t_env *e, t_sphere *sphere, t_ray ray)
{
	double		a;
	double		b;
	double		c;
	double		delta;

	(void)e;
	a = pow(ray.vector.x, 2) + pow(ray.vector.y, 2) + pow(ray.vector.z, 2);
	b = 2 * ((ray.vector.x * (ray.origin.x)) + ((ray.origin.y) * ray.vector.y)
			+ ((ray.origin.z) * ray.vector.z));
	c = pow(ray.origin.x, 2) + pow(ray.origin.y, 2) + pow(ray.origin.z, 2)
		- pow(sphere->radius, 2);
	delta = pow(b, 2) - (4 * a * c);
	if (sphere->height == 0)
		return (check_min(delta, a, b, c));
	return (caps_sphere(sphere, ray, check_min(delta, a, b, c),
	get_max(delta, a, b, c)));
}
