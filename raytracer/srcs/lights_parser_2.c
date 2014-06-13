/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_parser_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 14:50:14 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:50:20 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <libft.h>

static int		parse_light_line_item_2(t_env *e, char *tmp, int fd)
{
	if (ft_strncmp("point", tmp, 5) == 0)
	{
		add_or_create_list(&(e->lights), new_light(POINT), sizeof(t_light));
		trim_to_double_point(&tmp);
		parse_item(fd, e, tmp, &parse_light);
	}
	else if (ft_strncmp("spot", tmp, 4) == 0)
	{
		add_or_create_list(&(e->lights), new_light(SPOT), sizeof(t_light));
		trim_to_double_point(&tmp);
		parse_item(fd, e, tmp, &parse_light);
	}
	return (0);
}

int				parse_light_line_item(t_env *e, char **tab, int fd)
{
	int		j;
	char	*tmp;

	tmp = NULL;
	j = 0;
	while (tab[j])
	{
		tmp = ft_strtrim(tab[j]);
		if (parse_light_line_item_2(e, tmp, fd))
			return (1);
		if (ft_strncmp("}", tmp, 1) == 0)
			return (1);
		else if (ft_strncmp("point", tmp, 5) != 0
				&& ft_strncmp("spot", tmp, 4) != 0)
			file_error(4, tmp, "lights");
		j++;
		if (tmp[ft_strlen(tmp) - 1] == '}')
			return (1);
	}
	return (0);
}
