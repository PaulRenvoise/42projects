/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 17:08:23 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/22 17:36:03 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_color(t_env *env, t_coords *tmp, t_coords *tmp2, int max)
{
	if (tmp->z < (max / 2) && tmp2->z < (max / 2))
		env->color = 0x568203;
	else if (tmp->z < (max - (max / 3)) && tmp->z >= (max / 2))
		env->color = 0x88421D;
	else if (tmp->z <= max && tmp->z >= (max - (max / 3)) && tmp2->z <= max
			&& tmp2->z >= (max - (max / 3)))
		env->color = 0xFFFFFF;
	else
		env->color = 0x568203;
}

static void		draw_vlines(t_env *env, t_list *lstcoords)
{
	int			d;
	int			i;
	int			max;
	t_coords	*tmp;
	t_coords	*tmp2;

	i = 0;
	max = get_max_size(lstcoords);
	while (i + (tmp2 = lstcoords->content)->w <= ft_lstsize(lstcoords))
	{
		tmp = ft_lstget(lstcoords, i)->content;
		tmp2 = ft_lstget(lstcoords, i + tmp2->w)->content;
		d = tmp2->x;
		while (d <= tmp->x)
		{
			set_color(env, tmp, tmp2, max);
			if (tmp2->x == tmp->x - TH)
				mlx_pixel_put(env->mlx, env->win, d, tmp->y
						+ ((tmp2->y - tmp->y) * (d - tmp->x))
						/ (tmp2->x - tmp->x), env->color);
			d++;
		}
		i++;
	}
}

static void		draw_hlines(t_env *env, t_list *lstcoords)
{
	int			d;
	int			i;
	int			max;
	t_coords	*tmp;
	t_coords	*tmp2;

	i = 1;
	max = get_max_size(lstcoords);
	while (i + 1 <= ft_lstsize(lstcoords))
	{
		tmp = ft_lstget(lstcoords, i)->content;
		tmp2 = ft_lstget(lstcoords, i + 1)->content;
		d = tmp->x;
		while (d <= tmp2->x)
		{
			set_color(env, tmp, tmp2, max);
			mlx_pixel_put(env->mlx, env->win, d, tmp->y
					+ ((tmp2->y - tmp->y) * (d - tmp->x))
					/ (tmp2->x - tmp->x), env->color);
			d++;
		}
		i++;
	}
	draw_vlines(env, lstcoords);
}

static void		twod_to_iso(t_list **lstcoords, t_coords *xyz)
{
	t_coords	iso;

	iso.x = (xyz->x * TW) - (xyz->y * TH) + (WW / 2);
	iso.y = ((xyz->y * TH) + (xyz->x * TW) + (WH / 2)) / 2 - xyz->z;
	iso.z = xyz->z;
	iso.w = xyz->w;
	ft_lstnew_or_add(lstcoords, &iso, sizeof(t_list), 1);
}

int				get_coords(t_env *env)
{
	t_list		*tmp;
	t_list		*lstcoords;
	t_coords	xyz;

	tmp = NULL;
	lstcoords = NULL;
	xyz.y = 0;
	while (env->lst)
	{
		tmp = env->lst->content;
		xyz.w = ft_lstsize(tmp->next);
		xyz.x = 0;
		while (tmp->next)
		{
			xyz.x++;
			xyz.z = ft_atoi(tmp->content);
			twod_to_iso(&lstcoords, &xyz);
			tmp = tmp->next;
		}
		env->lst = env->lst->next;
		xyz.y++;
	}
	draw_hlines(env, lstcoords);
	return (0);
}
