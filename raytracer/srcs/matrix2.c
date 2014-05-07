/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 11:13:23 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:57:36 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>
#include <stdlib.h>

void			create_mat_shadow(t_env *e)
{
	int		k;
	t_pos	pos;
	double	ix;
	double	iy;

	ix = -(((RAY_SHADOW - 1) / 2) / 100);
	pos.x = 0;
	k = 0;
	e->mx = (double *)malloc(sizeof(double) * RAY_SHADOW);
	e->my = (double *)malloc(sizeof(double) * RAY_SHADOW);
	while (pos.x < sqrt(RAY_SHADOW))
	{
		pos.y = 0;
		iy = -(((RAY_SHADOW - 1) / 2) / 100);
		pos.x++;
		while (pos.y < sqrt(RAY_SHADOW))
		{
			e->mx[k] = ix;
			e->my[k] = iy;
			k++;
			pos.y++;
			iy += 0.003;
		}
		ix += 0.003;
	}
}

static void		create_var(t_var *v, t_coord rotation)
{
	v->a = cos(rotation.x * (M_PI / 180));
	v->b = sin(rotation.x * (M_PI / 180));
	v->c = cos(rotation.y * (M_PI / 180));
	v->d = sin(rotation.y * (M_PI / 180));
	v->e = cos(rotation.z * (M_PI / 180));
	v->f = sin(rotation.z * (M_PI / 180));
}

double			*transf_matrix(t_coord rotation, t_coord translation)
{
	t_var	v;
	double	*matrix;

	create_var(&v, rotation);
	matrix = (double *)malloc(sizeof(double) * 16);
	matrix[0] = v.c * v.e;
	matrix[1] = -(v.c * v.f);
	matrix[2] = -v.d;
	matrix[3] = translation.x;
	matrix[4] = ((-1) * (v.b * v.d * v.e)) + (v.a * v.f);
	matrix[5] = ((-1) * (v.b * v.d * v.f)) + (v.a * v.e);
	matrix[6] = -(v.b * v.c);
	matrix[7] = translation.y;
	matrix[8] = ((v.a * v.d * v.e) + (v.b * v.f));
	matrix[9] = ((-1) * (v.a * v.d * v.f)) + (v.b * v.e);
	matrix[10] = v.a * v.c;
	matrix[11] = translation.z;
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1;
	return (matrix);
}

double			*get_matrix(t_object *object)
{
	double	*matrix;

	matrix = NULL;
	if (object->type == SPHERE)
		matrix = transf_matrix(((t_sphere *)(object->object))->rotation,
				((t_sphere *)(object->object))->position);
	else if (object->type == PLANE)
		matrix = transf_matrix(((t_plane *)(object->object))->rotation,
				((t_plane *)(object->object))->position);
	else if (object->type == CYLINDER)
		matrix = transf_matrix(((t_cylinder *)(object->object))->rotation,
				((t_cylinder *)(object->object))->position);
	else if (object->type == CONE)
		matrix = transf_matrix(((t_cone *)(object->object))->rotation,
				((t_cone *)(object->object))->position);
	else if (object->type == CUBE)
		matrix = transf_matrix(((t_cube *)(object->object))->rotation,
				((t_cube *)(object->object))->position);
	return (matrix);
}
