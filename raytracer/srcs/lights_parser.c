/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 14:49:44 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:49:59 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <libft.h>
#include <stdlib.h>

t_light			*new_light(int type)
{
	t_light		*new;

	new = (t_light *)malloc(sizeof(t_light));
	if (new)
	{
		new->type = type;
		new->position.x = 0;
		new->position.y = 0;
		new->position.z = 0;
		new->rotation.x = 0;
		new->rotation.y = 0;
		new->rotation.z = 0;
		new->color.r = 0;
		new->color.g = 0;
		new->color.b = 0;
		new->intensity = 0;
		return (new);
	}
	else
		return (NULL);
}

static int		parse_light_item_2(t_env *e, char *tmp)
{
	if (ft_strncmp("position", tmp, 8) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_position(tmp, &(((t_light *)(e->lights->content))->position)))
			return (1);
	}
	else if (ft_strncmp("rotation", tmp, 8) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_rotation(tmp, &(((t_light *)(e->lights->content))->rotation)))
			return (1);
	}
	else if (ft_strncmp("color", tmp, 5) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_color(tmp, &(((t_light *)(e->lights->content))->color)))
			return (1);
	}
	if (ft_strncmp("intensity", tmp, 8) == 0)
	{
		trim_to_double_point(&tmp);
		if (parse_size(tmp, &(((t_light *)(e->lights->content))->intensity)))
			return (1);
	}
	return (0);
}

static int		parse_light_item(t_env *e, char **tab)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = NULL;
	while (tab[j])
	{
		tmp = ft_strtrim(tab[j]);
		if (parse_light_item_2(e, tmp))
			return (1);
		if (ft_strncmp("}", tmp, 1) == 0)
			return (1);
		else if (ft_strncmp("position", tmp, 8) != 0
				&& ft_strncmp("rotation", tmp, 8) != 0
				&& ft_strncmp("color", tmp, 5) != 0
				&& ft_strncmp("intensity", tmp, 8) != 0)
			file_error(4, tmp, "light");
		j++;
	}
	return (0);
}

int				parse_light(t_env *e, char *line, int *i, int fd)
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
		if (parse_light_item(e, tab))
			return (1);
	}
	if (i > 0 && line[0] == '}' && line[1] == '\0')
		return (1);
	return (0);
}

int				parse_lights_line(t_env *e, char *line, int *i, int fd)
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
		if (parse_light_line_item(e, tab, fd))
			return (1);
	}
	if (i > 0 && line[0] == '}' && line[1] == '\0')
		return (1);
	return (0);
}
