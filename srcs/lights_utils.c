/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 15:34:38 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 17:39:40 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <stdlib.h>

void	adjust_color(t_color *new_color)
{
	if (new_color->r > 255)
		new_color->r = 255;
	if (new_color->g > 255)
		new_color->g = 255;
	if (new_color->b > 255)
		new_color->b = 255;
	if (new_color->r < 0)
		new_color->r = 0;
	if (new_color->g < 0)
		new_color->g = 0;
	if (new_color->b < 0)
		new_color->b = 0;
}

int		check_intersec_light(double *intersec, t_coord inter, t_ray spot)
{
	t_coord	inter_light;
	int		check;

	check = 0;
	if (*intersec < 0)
	{
		inter_light = pt_inter(spot, *intersec);
		if (norm_vect(vectorize(inter_light, spot.origin))
				< norm_vect(vectorize(inter, spot.origin)) - 0.01)
			check = 1;
	}
	return (check);
}
