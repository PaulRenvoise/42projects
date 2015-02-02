/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 17:40:47 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 16:37:12 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

void	ambiant(t_color *new_color, t_color old, t_object *object)
{
	new_color->r += object->material.ambiant * old.r;
	new_color->g += object->material.ambiant * old.g;
	new_color->b += object->material.ambiant * old.b;
}

void	diffuse(t_color *new_color, t_color old, t_object *object, double diff)
{
	new_color->r += (old.r * object->material.diffuse * diff);
	new_color->g += (old.g * object->material.diffuse * diff);
	new_color->b += (old.b * object->material.diffuse * diff);
}

void	specular(t_vlight *vl, t_ray spot, t_coord normal)
{
	t_coord	reflection;
	double	spec;

	reflection.x = (normal.x * 2 * dot_product(normal, spot.vector))
					- spot.vector.x;
	reflection.y = (normal.y * 2 * dot_product(normal, spot.vector))
					- spot.vector.y;
	reflection.z = (normal.z * 2 * dot_product(normal, spot.vector))
					- spot.vector.z;
	reflection = normalize(reflection);
	spec = pow(fmax(0, dot_product(reflection, spot.vector)),
			vl->object->material.phong);
	vl->col->r += vl->old.r * (spec * vl->object->material.specular);
	vl->col->g += vl->old.g * (spec * vl->object->material.specular);
	vl->col->b += vl->old.b * (spec * vl->object->material.specular);
}
