/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 14:53:43 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:53:44 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <get_next_line.h>
#include <libft.h>

static t_object	*new_obj(int type, void *obj)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (new)
	{
		new->type = type;
		new->object = obj;
		return (new);
	}
	else
		return (NULL);
}

static void		parse_object_create_object(char **tmp, int type, t_env *e)
{
	add_or_create_list(&(e->objects), new_obj(type, new_sphere()),
						sizeof(t_object));
	*tmp = &(ft_strchr(*tmp, ':'))[1];
	*tmp = ft_strtrim(*tmp);
}

static int		parse_object_check_item_2(t_env *e, char *tmp, int fd)
{
	if (ft_strncmp("sphere", tmp, 6) == 0)
	{
		parse_object_create_object(&tmp, SPHERE, e);
		parse_item(fd, e, tmp, &parse_sphere);
		return (1);
	}
	else if (ft_strncmp("plane", tmp, 5) == 0)
	{
		parse_object_create_object(&tmp, PLANE, e);
		parse_item(fd, e, tmp, &parse_plane);
		return (1);
	}
	else if (ft_strncmp("cube", tmp, 4) == 0)
	{
		parse_object_create_object(&tmp, CUBE, e);
		parse_item(fd, e, tmp, &parse_cube);
		return (1);
	}
	else if (ft_strncmp("cylinder", tmp, 8) == 0)
	{
		parse_object_create_object(&tmp, CYLINDER, e);
		parse_item(fd, e, tmp, &parse_cylinder);
		return (1);
	}
	return (0);
}

static int		parse_object_check_item(t_env *e, char **tab, int fd, char *tmp)
{
	int		j;

	j = 0;
	while (tab[j])
	{
		tmp = ft_strtrim(tab[j]);
		if (parse_object_check_item_2(e, tmp, fd))
		{
		}
		else if (ft_strncmp("cone", tmp, 4) == 0)
		{
			parse_object_create_object(&tmp, CONE, e);
			parse_item(fd, e, tmp, &parse_cone);
		}
		else if (ft_strncmp("}", tmp, 1) == 0)
			return (1);
		else
			file_error(4, tmp, "objects");
		j++;
		if (tmp[ft_strlen(tmp) - 1] == '}')
			return (1);
	}
	return (0);
}

int				parse_objects_line(t_env *e, char *line, int *i, int fd)
{
	char	**tab;
	char	*tmp;

	tmp = NULL;
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
		if (parse_object_check_item(e, tab, fd, tmp))
			return (1);
	}
	if (i > 0 && line[0] == '}' && line[1] == '\0')
		return (1);
	return (0);
}
