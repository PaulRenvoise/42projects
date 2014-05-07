/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplittoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/02 13:59:23 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:43:06 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_size(char *s, char c)
{
	int			i;
	size_t		res;

	res = 0;
	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
		res++;
	}
	return (res);
}

static void		ft_fill(int nb, char c, int *tab, char *s)
{
	int			i;
	int			j;
	size_t		size;

	size = 0;
	i = 0;
	j = 0;
	while (s[i] && j < nb)
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) || (s[0] != c && i == 0))
		{
			if (s[i] == c)
				i++;
			size = ft_size(&s[i], c);
			tab[j] = ft_atoi(ft_strsub(s, (unsigned int)i, size));
			j++;
		}
		i++;
	}
}

int				*ft_strsplittoi(char const *s, char c)
{
	int			*tab;
	int			nb;
	int			i;

	i = -1;
	nb = 0;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) || (s[0] != c && i == 0))
			nb++;
	}
	if (!(tab = (int*)malloc(sizeof(int*) * (size_t)(nb + 1))))
		return (NULL);
	ft_fill(nb, c, tab, (char*)s);
	tab[nb] = '\0';
	return (tab);
}
