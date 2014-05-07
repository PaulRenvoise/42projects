/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 12:33:46 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 20:49:52 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

t_coord		vectorize(t_coord a, t_coord b)
{
	t_coord	vector;

	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	vector.z = b.z - a.z;
	return (vector);
}

double		norm_vect(t_coord vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

double		dot_product(t_coord a, t_coord b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_coord		normalize(t_coord vect)
{
	t_coord	normal;

	normal.x = vect.x / norm_vect(vect);
	normal.y = vect.y / norm_vect(vect);
	normal.z = vect.z / norm_vect(vect);
	return (normal);
}

t_coord		pt_inter(t_ray ray, double t)
{
	t_coord	inter;

	inter.x = ray.origin.x + (ray.vector.x * t);
	inter.y = ray.origin.y + (ray.vector.y * t);
	inter.z = ray.origin.z + (ray.vector.z * t);
	return (inter);
}
