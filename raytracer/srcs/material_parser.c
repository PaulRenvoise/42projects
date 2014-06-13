/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 14:54:04 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:59:14 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <get_next_line.h>
#include <libft.h>
#include <ft_atof.h>
#include <fcntl.h>
#include <stdio.h>

static int	parse_material_item_4(t_env *e, char *tmp)
{
	if (ft_strncmp("refraction", tmp, 10) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_object *)
						(e->objects->content))->material.refraction)))
			return (1);
	}
	if (ft_strncmp("color", tmp, 5) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_color(tmp, &(((t_object *)
						(e->objects->content))->material.color)))
			return (1);
	}
	if (ft_strncmp("}", tmp, 1) == 0)
		return (1);
	return (0);
}

static int	parse_material_item_3(t_env *e, char *tmp)
{
	if (ft_strncmp("phong", tmp, 5) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_object *)
						(e->objects->content))->material.phong)))
			return (1);
	}
	if (ft_strncmp("transparency", tmp, 12) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_object *)
						(e->objects->content))->material.transparency)))
			return (1);
	}
	if (ft_strncmp("reflection", tmp, 10) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_object *)
						(e->objects->content))->material.reflection)))
			return (1);
	}
	if (parse_material_item_4(e, tmp))
		return (1);
	return (0);
}

static int	parse_material_item_2(t_env *e, char *tmp)
{
	if (ft_strncmp("ambiant", tmp, 7) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_object *)
						(e->objects->content))->material.ambiant)))
			return (1);
	}
	if (ft_strncmp("diffuse", tmp, 7) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_object *)
						(e->objects->content))->material.diffuse)))
			return (1);
	}
	if (ft_strncmp("specular", tmp, 4) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_object *)
						(e->objects->content))->material.specular)))
			return (1);
	}
	if (parse_material_item_3(e, tmp))
		return (1);
	return (0);
}

static int	parse_material_item(t_env *e, char **tab)
{
	int		j;
	char	*tmp;

	tmp = NULL;
	j = 0;
	while (tab[j])
	{
		tmp = ft_strtrim(tab[j]);
		if (parse_material_item_2(e, tmp))
			return (1);
		else if (ft_strncmp("ambiant", tmp, 7) != 0
			&& ft_strncmp("diffuse", tmp, 7) != 0
			&& ft_strncmp("specular", tmp, 4) != 0
			&& ft_strncmp("phong", tmp, 5) != 0
			&& ft_strncmp("reflection", tmp, 10) != 0
			&& ft_strncmp("refraction", tmp, 10) != 0
			&& ft_strncmp("transparency", tmp, 12) != 0
			&& ft_strncmp("color", tmp, 5) != 0)
			file_error(4, tmp, "material");
		j++;
		if (tmp[ft_strlen(tmp) - 1] == '}')
			return (1);
	}
	return (0);
}

int			parse_material_line(t_env *e, char *line, int *i, int fd)
{
	char	**tab;

	(void)fd;
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
		if (parse_material_item(e, tab))
			return (1);
	}
	if (i > 0 && line[0] == '}' && line[1] == '\0')
		return (1);
	return (0);
}
