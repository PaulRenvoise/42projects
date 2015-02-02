/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 14:16:03 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 17:47:30 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>
#include <stdlib.h>

static void	normal_plane(t_coord *normal)
{
	normal->x = 0;
	normal->y = -1;
	normal->z = 0;
}

static void	normal_cylinder(t_coord *normal, t_coord inter)
{
	t_coord	proj;

	proj.x = 0;
	proj.y = inter.y;
	proj.z = 0;
	*normal = normalize(vectorize(proj, inter));
}

static void	normal_cone(t_cone *cone, t_coord *normal, t_coord inter)
{
	t_coord	proj;
	double	len;
	double	dow;

	proj.x = 0;
	proj.y = inter.y;
	proj.z = 0;
	len = norm_vect(vectorize(inter, proj));
	dow = len * tan(cone->radius * (M_PI / 180));
	if (proj.y >= 0)
		proj.y += dow;
	else
		proj.y += dow;
	*normal = normalize(vectorize(proj, inter));
}

static void	normal_cube(t_env *e, t_coord *normal)
{
	normal->x = 0;
	normal->y = 0;
	normal->z = 0;
	if (e->face == 1)
		normal->y = 1;
	else if (e->face == 2)
		normal->x = -1;
	else if (e->face == 3)
		normal->z = 1;
	else if (e->face == 4)
		normal->y = -1;
	else if (e->face == 5)
		normal->x = 1;
	else if (e->face == 6)
		normal->z = -1;
}

void		calculate_normal(t_env *e, t_coord *normal, t_object *object,
			t_coord inter)
{
	double	*matrix;

	matrix = get_matrix(object);
	if (object->type == SPHERE)
		*normal = normalize(inter);
	else if (object->type == PLANE)
		normal_plane(normal);
	else if (object->type == CYLINDER)
		normal_cylinder(normal, inter);
	else if (object->type == CONE)
		normal_cone((t_cone *)(object->object), normal, inter);
	else if (object->type == CUBE)
		normal_cube(e, normal);
	matrix = invert_matrix(matrix);
	matrix = trans_matrix(matrix);
	*normal = transf_vector(*normal, matrix);
	*normal = normalize(*normal);
	if (e->direction)
	{
		(*normal).x *= -1;
		(*normal).y *= -1;
		(*normal).z *= -1;
	}
}
