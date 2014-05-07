/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 16:48:59 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 16:58:20 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

static double	square(t_plane *plane, t_coord inter, double t)
{
	double	k1;
	double	k2;
	t_coord	vect1;
	t_coord	vect2;

	vect1.x = plane->width;
	vect1.y = 0;
	vect1.z = 0;
	vect2.x = 0;
	vect2.y = 0;
	vect2.z = plane->height;
	k2 = ((vect1.x * inter.z) - (inter.x * vect1.z)) / ((vect2.z * vect1.x)
			- (vect1.z * vect2.x));
	k1 = (inter.x - (k2 * vect2.x)) / vect1.x;
	if ((k1 > 0 && k1 < 1) && (k2 > 0 && k2 < 1))
		if (t >= 0.001)
			return (t);
	return (0);
}

double			intersection_plane(t_env *e, t_plane *plane, t_ray ray)
{
	double	t;
	t_coord	inter;

	(void)e;
	if (ray.vector.y == 0)
		return (0);
	else
	{
		t = -(ray.origin.y / ray.vector.y);
		inter = pt_inter(ray, t);
		if (plane->radius)
		{
			if (t >= 0.001 && pow(inter.x, 2) + pow(inter.z, 2)
					< pow(plane->radius, 2))
				return (t);
		}
		else if (plane->width || plane->height)
			return (square(plane, inter, t));
		else
		{
			if (t >= 0.001)
				return (t);
		}
	}
	return (0);
}

static t_plane	init_plane(t_cube *cube, int i)
{
	t_plane	plane;

	plane.position = cube->position;
	plane.rotation = cube->rotation;
	plane.width = cube->width;
	plane.height = cube->height;
	plane.radius = 0;
	if (i == 2)
		plane.rotation.z += -90;
	if (i == 3)
	{
		plane.rotation.x += 90;
		plane.position.z += cube->width;
	}
	if (i == 4)
		plane.position.y -= cube->height;
	if (i == 5)
	{
		plane.position.x += cube->width;
		plane.rotation.z += -90;
	}
	if (i == 6)
		plane.rotation.x += 90;
	return (plane);
}

double			intersection_cube(t_env *e, t_cube *cube, t_ray ray)
{
	t_plane	plane;
	double	ktest;
	double	kmin;
	t_ray	ray_save;
	int		i;

	i = 1;
	kmin = -1;
	ray_save = transf_ray(ray, transf_matrix(cube->rotation, cube->position));
	while (i < 7)
	{
		ray = ray_save;
		plane = init_plane(cube, i);
		ray = transf_ray(ray, invert_matrix(transf_matrix(plane.rotation,
						plane.position)));
		ktest = intersection_plane(e, &plane, ray);
		if (ktest != 0 && (kmin == -1 || ktest < kmin))
		{
			e->face = i;
			kmin = ktest;
		}
		i++;
	}
	return (kmin == -1 ? 0 : kmin);
}
