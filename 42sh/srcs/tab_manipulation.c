/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msagodir <msagodir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/18 15:19:45 by msagodir          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

void			free_strtab(char **tab)
{
	int			i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
}

int				strtablen(char **tab)
{
	int			i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char			**tab_add_end(char **src, char **toadd)
{
	int			i;
	int			j;
	int			len;
	char		**tab;

	len = strtablen(src) + strtablen(toadd);
	i = strtablen(src);
	j = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (size_t)(len + 1))))
		print_err("Malloc()", MALLOC);
	while (j < i)
	{
		tab[j] = ft_strdup(src[j]);
		j++;
	}
	i = 0;
	tab[len] = NULL;
	while (toadd[i])
	{
		tab[j] = ft_strdup(toadd[i]);
		i++;
		j++;
	}
	free_strtab(src);
	return (tab);
}

char			**tabjoin(char **tab1, char **tab2, int index, int k)
{
	int			j;
	int			len;

	len = strtablen(tab1) + strtablen(tab2);
	j = len - 2;
	if (!(tab1 = ft_realloc(tab1, sizeof(char *) * (size_t)(len))))
		exit(EXIT_FAILURE);
	tab1[len - 1] = NULL;
	while (k > index)
	{
		if (tab1[k] != NULL)
		{
			tab1[j] = tab1[k];
			j--;
		}
		k--;
	}
	j = 0;
	while (tab2[j] != NULL)
	{
		tab1[index] = tab2[j];
		j++;
		index++;
	}
	return (tab1);
}
