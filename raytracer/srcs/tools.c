/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 20:12:17 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:59:32 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <libft.h>
#include <stdlib.h>

void		add_or_create_list(t_list **addto, void *toadd, int size)
{
	if (*addto == NULL)
		*addto = ft_lstnew(toadd, size);
	else
		ft_lstadd(addto, ft_lstnew(toadd, size));
}

void		trim_to_double_point(char **tmp)
{
	*tmp = &(ft_strchr(*tmp, ':'))[1];
	*tmp = ft_strtrim(*tmp);
}

int			not_double(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit && str[i] != '.')
			return (1);
		i++;
	}
	return (0);
}

int			not_int(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit)
			return (1);
		i++;
	}
	return (0);
}
