/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:56:43 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 19:43:16 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void			calc_color(t_color *col, t_color *col2, t_color old,
				double coef)
{
	col->r = ((col2->r * coef)) + (old.r * (1 - coef));
	col->g = ((col2->g * coef)) + (old.g * (1 - coef));
	col->b = ((col2->b * coef)) + (old.b * (1 - coef));
}

t_coord			calc_transparency(t_coord normal, t_coord vector, double sqroot,
				double n)
{
	t_coord		transparency;

	transparency.x = n * vector.x + (((-1) * n * (dot_product(normal, vector))
				- sqroot) * normal.x);
	transparency.y = n * vector.y + (((-1) * n * (dot_product(normal, vector))
				- sqroot) * normal.y);
	transparency.z = n * vector.z + (((-1) * n * (dot_product(normal, vector))
				- sqroot) * normal.z);
	transparency = normalize(transparency);
	return (transparency);
}

t_coord			calc_reflection(t_coord normal, t_coord vector)
{
	t_coord		reflection;

	reflection.x = -(normal.x * 2) * dot_product(normal, vector) + vector.x;
	reflection.y = -(normal.y * 2) * dot_product(normal, vector) + vector.y;
	reflection.z = -(normal.z * 2) * dot_product(normal, vector) + vector.z;
	reflection = normalize(reflection);
	return (reflection);
}
