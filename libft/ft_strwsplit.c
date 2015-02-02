/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/17 16:58:58 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:43:48 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_size(char *s)
{
	int			i;
	size_t		res;

	res = 0;
	i = 0;
	while (s[i] != ' ' && s[i] != '\t' && s[i])
	{
		i++;
		res++;
	}
	return (res);
}

static void		ft_fill(int nb, char **tab, char *s)
{
	int			i;
	int			j;
	size_t		size;

	size = 0;
	i = 0;
	j = 0;
	while (s[i] && j < nb)
	{
		if (((s[i] == ' ' || s[i] == '\t')
			&& s[i + 1] != ' ' && s[i + 1] != '\t' && s[i + 1])
			|| (s[0] != ' ' && s[0] != '\t' && i == 0))
		{
			if (s[i] == ' ' || s[i] == '\t')
				i++;
			size = ft_size(&s[i]);
			tab[j] = ft_strsub(s, (unsigned int)i, size);
			j++;
		}
		i++;
	}
}

char			**ft_strwsplit(char const *s)
{
	char		**tab;
	int			nb;
	int			i;

	i = -1;
	nb = 0;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (((s[i] == ' ' || s[i] == '\t')
			&& s[i + 1] != ' ' && s[i + 1] != '\t' && s[i + 1])
			|| (s[0] != ' ' && s[0] != '\t' && i == 0))
			nb++;
	}
	if (!(tab = (char**)malloc(sizeof(char**) * (size_t)(nb + 1))))
		return (NULL);
	ft_fill(nb, tab, (char*)s);
	tab[nb] = '\0';
	return (tab);
}
