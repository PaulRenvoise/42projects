/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbrieuc <rbrieuc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 15:45:06 by rbrieuc           #+#    #+#             */
/*   Updated: 2014/03/27 17:39:08 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

static void		increment(t_env *e, t_coord *vector, int i)
{
	vector->x += e->mx[i];
	vector->y += e->my[i];
}

static double	shadows2(t_env *e, t_list *objects, t_coord inter, int i)
{
	t_ray	spot_save;
	double	intersec;
	double	nb;

	nb = 0;
	spot_save = e->spot;
	increment(e, &(e->spot.vector), i);
	while (objects)
	{
		test_objects(e, objects, &e->spot, &intersec);
		if (check_intersec_light(&intersec, inter, spot_save))
		{
			nb++;
			break ;
		}
		objects = objects->next;
		e->spot = spot_save;
		increment(e, &(e->spot.vector), i);
	}
	e->spot = spot_save;
	return (nb);
}

static t_object	*get_object(t_env *e, t_list *objects, t_coord inter)
{
	t_ray		spot_save;
	double		intersec;

	spot_save = e->spot;
	while (objects)
	{
		test_objects(e, objects, &e->spot, &intersec);
		if (check_intersec_light(&intersec, inter, spot_save))
			return ((t_object *)objects->content);
		objects = objects->next;
		e->spot = spot_save;
	}
	e->spot = spot_save;
	return (NULL);
}

double			shadows(t_env *e, t_list *objects, t_coord inter)
{
	int			i;
	double		nb;
	t_object	*object;

	nb = 0;
	i = 0;
	while (i < RAY_SHADOW)
	{
		nb += shadows2(e, objects, inter, i);
		i++;
	}
	object = get_object(e, objects, inter);
	if (object)
		return (fmax(1, ((nb / RAY_SHADOW) + 1)
		- object->material.transparency));
	return (1);
}
