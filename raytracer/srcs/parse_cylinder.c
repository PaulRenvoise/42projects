/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 14:31:38 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 17:55:05 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <libft.h>
#include <stdlib.h>

t_cylinder		*new_cylinder(void)
{
	t_cylinder	*new;

	new = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (new)
	{
		new->position.x = 0;
		new->position.y = 0;
		new->position.z = 0;
		new->rotation.x = 0;
		new->rotation.y = 0;
		new->rotation.z = 0;
		new->radius = 0;
		new->height = 0;
		new->caps = 0;
		return (new);
	}
	else
		return (NULL);
}

static int		parse_cylinder_item_2(t_env *e, char *tmp)
{
	if (ft_strncmp("position", tmp, 8) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_position(tmp, &(((t_cylinder *)(((t_object *)
							(e->objects->content))->object)))->position))
			return (1);
	}
	if (ft_strncmp("rotation", tmp, 8) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_rotation(tmp, &(((t_cylinder *)(((t_object *)
							(e->objects->content))->object)))->rotation))
			return (1);
	}
	if (ft_strncmp("radius", tmp, 6) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_cylinder *)(((t_object *)
						(e->objects->content))->object)))->radius))
			return (1);
	}
	return (0);
}

static int		parse_cylinder_item_3(t_env *e, char *tmp, int fd)
{
	if (ft_strncmp("height", tmp, 6) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_cylinder *)(((t_object *)
						(e->objects->content))->object)))->height))
			return (1);
	}
	if (ft_strncmp("material", tmp, 8) == 0)
	{
		trim_to_double_point(&tmp);
		parse_item(fd, e, tmp, &parse_material_line);
	}
	if (ft_strncmp("caps", tmp, 4) == 0)
	{
		trim_to_double_point(&tmp);
		(((t_cylinder *)(((t_object *)
		(e->objects->content))->object)))->caps = ft_atoi(tmp);
	}
	if (ft_strncmp("}", tmp, 1) == 0)
		return (1);
	return (0);
}

static int		parse_cylinder_item(t_env *e, char **tab, int fd)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	j = 0;
	while (tab[j])
	{
		tmp = ft_strtrim(tab[j]);
		if (parse_cylinder_item_2(e, tmp))
			return (1);
		else if (parse_cylinder_item_3(e, tmp, fd))
			return (1);
		else if (ft_strncmp("position", tmp, 8) != 0
				&& ft_strncmp("rotation", tmp, 8) != 0
				&& ft_strncmp("radius", tmp, 6) != 0
				&& ft_strncmp("height", tmp, 6) != 0
				&& ft_strncmp("caps", tmp, 4) != 0
				&& ft_strncmp("material", tmp, 8) != 0
				&& ft_strncmp("}", tmp, 1) != 0)
			file_error(4, tmp, "cylinder");
		j++;
		if (tmp[ft_strlen(tmp) - 1] == '}')
			return (1);
	}
	return (0);
}

int				parse_cylinder(t_env *e, char *line, int *i, int fd)
{
	char	**tab;

	if (*i == 0)
	{
		if (line[0] != '{')
			file_error(2, NULL, NULL);
		if (line[1] != '\0')
			line = &(line)[1];
		(*i)++;
	}
	if (*i > 0 && line[1] != '\0')
	{
		tab = ft_strsplit(line, ',');
		if (parse_cylinder_item(e, tab, fd))
			return (1);
	}
	if (i > 0 && line[0] == '}' && line[1] == '\0')
		return (1);
	return (0);
}
