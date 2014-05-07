/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 14:46:53 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:46:54 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <libft.h>
#include <ft_atof.h>

int		parse_color(char *str, t_color *c)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		if (not_int(tab[i]))
			file_error(6, NULL, NULL);
		if (i == 0)
			c->r = ft_atoi(tab[i]);
		else if (i == 1)
			c->g = ft_atoi(tab[i]);
		else if (i == 2)
			c->b = ft_atoi(tab[i]);
		else if (ft_strcmp(tab[i], "}") == 0)
			return (1);
		else
			file_error(5, "color", NULL);
		i++;
	}
	return (0);
}

int		parse_size(char *str, double *size)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		if (not_double(tab[i]))
			file_error(6, NULL, NULL);
		if (i == 0)
			*size = ft_atof(tab[i]);
		else if (ft_strcmp(tab[i], "}") == 0)
			return (1);
		else
			file_error(5, "double expected", NULL);
		i++;
	}
	return (0);
}

int		parse_position(char *str, t_coord *pos)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		if (not_double(tab[i]))
			file_error(6, NULL, NULL);
		if (i == 0)
			pos->x = ft_atof(tab[i]);
		else if (i == 1)
			pos->y = ft_atof(tab[i]);
		else if (i == 2)
			pos->z = ft_atof(tab[i]);
		else if (ft_strcmp(tab[i], "}") == 0)
			return (1);
		else
			file_error(5, "position", NULL);
		i++;
	}
	return (0);
}

int		parse_rotation(char *str, t_coord *rot)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		if (not_double(tab[i]))
			file_error(6, NULL, NULL);
		if (i == 0)
			rot->x = ft_atof(tab[i]);
		else if (i == 1)
			rot->y = ft_atof(tab[i]);
		else if (i == 2)
			rot->z = ft_atof(tab[i]);
		else if (ft_strcmp(tab[i], "}") == 0)
			return (1);
		else
			file_error(5, "rotation", NULL);
		i++;
	}
	return (0);
}
