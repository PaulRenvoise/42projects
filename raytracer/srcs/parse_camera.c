/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 14:29:47 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:29:52 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <libft.h>

static int	parse_cam_line_check_item(char **tab, char *tmp, int *j, t_env *e)
{
	while (tab[*j])
	{
		tmp = ft_strtrim(tab[*j]);
		if (ft_strncmp("position", tmp, 8) == 0)
		{
			tmp = &(ft_strchr(tmp, ':'))[1];
			tmp = ft_strtrim(tmp);
			if (parse_position(tmp, &(e->camera.position)))
				return (1);
		}
		else if (ft_strncmp("rotation", tmp, 8) == 0)
		{
			tmp = &(ft_strchr(tmp, ':'))[1];
			tmp = ft_strtrim(tmp);
			if (parse_rotation(tmp, &(e->camera.rotation)))
				return (1);
		}
		else if (tmp[ft_strlen(tmp) - 1] == '}')
			return (1);
		else
			file_error(4, tmp, "camera");
		(*j)++;
	}
	return (0);
}

int			parse_cam_line(t_env *e, char *line, int *i, int fd)
{
	int		j;
	char	**tab;
	char	*tmp;

	(void)fd;
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
		j = 0;
		if (parse_cam_line_check_item(tab, tmp, &j, e))
			return (0);
	}
	if (i > 0 && line[0] == '}' && line[1] == '\0')
		return (1);
	return (0);
}
