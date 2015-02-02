/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/10 14:42:37 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 16:39:34 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <raytracer.h>
#include <stdlib.h>
#include <math.h>
#include <libft.h>

void			test_objects(t_env *e, t_list *objects, t_ray *spot, double *t)
{
	double	*matrix;

	matrix = get_matrix((t_object *)objects->content);
	*spot = transf_ray(*spot, invert_matrix(matrix));
	if (((t_object *)(objects->content))->type == SPHERE)
		*t = intersection_sphere(e, ((t_sphere *)(((t_object *)
							(objects->content))->object)), *spot);
	else if (((t_object *)(objects->content))->type == PLANE)
		*t = intersection_plane(e, ((t_plane *)(((t_object *)
							(objects->content))->object)), *spot);
	else if (((t_object *)(objects->content))->type == CYLINDER)
		*t = intersection_cylinder(e, ((t_cylinder *)(((t_object *)
							(objects->content))->object)), *spot);
	else if (((t_object *)(objects->content))->type == CONE)
		*t = intersection_cone(e, ((t_cone *)(((t_object *)
							(objects->content))->object)), *spot);
	else if (((t_object *)(objects->content))->type == CUBE)
		*t = intersection_cube(e, ((t_cube *)(((t_object *)
							(objects->content))->object)), *spot);
}

void			affect_min(t_reftrans *rt, t_min *min, t_object *object)
{
	if (min->dmin == -1 || norm_vect(vectorize((rt->ray).origin,
			pt_inter(rt->ray, rt->t))) < min->dmin)
	{
		min->tmin = rt->t;
		min->raymin = rt->ray;
		min->dmin = norm_vect(vectorize((rt->ray).origin,
					pt_inter(rt->ray, rt->t)));
		min->objectmin = object;
	}
}

t_object		*intersection(t_list *objects, t_env *e, t_reftrans *rt)
{
	t_min		min;
	t_ray		first_ray;

	min.dmin = -1;
	min.objectmin = NULL;
	min.tmin = 0;
	first_ray = rt->ray;
	while (objects)
	{
		if (((t_object *)(objects->content)) != rt->gc.ignore)
		{
			test_objects(e, objects, &rt->ray, &rt->t);
			if (rt->t > 0.01)
				affect_min(rt, &min, (t_object *)(objects->content));
		}
		objects = objects->next;
		rt->ray = first_ray;
	}
	rt->ray = min.raymin;
	rt->t = min.tmin;
	return (min.objectmin);
}

void			init_draw(t_env *e, t_getcolor *gc)
{
	gc->ignore = (t_object *)malloc(sizeof(t_object));
	gc->current = (t_object *)malloc(sizeof(t_object));
	gc->ignore = NULL;
	gc->current = NULL;
	gc->i = 0;
	mlx_string_put(e->mlx_info.mlx, e->mlx_info.win, WIN_WIDTH / 2 - 35,
			WIN_HEIGHT / 2 - 20, 0xFFFFFF, "Rendering...");
	e->pos.x = 0;
	e->direction = 0;
	create_mat_shadow(e);
}

void			draw(t_env *e)
{
	t_color		col;
	t_ray		ray;
	t_getcolor	gc;

	init_draw(e, &gc);
	init_view(e);
	while (e->pos.x < WIN_WIDTH)
	{
		e->pos.y = 0;
		while (e->pos.y < WIN_HEIGHT)
		{
			init_ray(e, &ray);
			get_color(e, ray, &col, gc);
			mlx_put_pixel_to_image(e, e->pos.x, e->pos.y, &col);
			if (e->pos.y > (WIN_HEIGHT / 2) - 10 && e->pos.y
					< (WIN_HEIGHT / 2) + 10)
				mlx_pixel_put(e->mlx_info.mlx, e->mlx_info.win, e->pos.x,
						e->pos.y, 0xFF0000);
			++e->pos.y;
		}
		++e->pos.x;
	}
	free(e->mx);
	free(e->my);
}
