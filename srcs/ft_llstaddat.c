/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstaddat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:13:49 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:27:00 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_llstaddnode(t_node **tmp, t_node **new)
{
	(*tmp)->next->prev = *new;
	(*tmp)->prev->next = *new;
	(*new)->prev = (*tmp)->prev;
	(*new)->next = *tmp;
}

void		ft_llstaddat(t_llist **allst, t_node *new, size_t pos)
{
	t_node	*tmp;
	size_t	i;

	if ((tmp = (*allst)->head))
	{
		i = 0;
		while (tmp && i != pos)
		{
			tmp = tmp->next;
			i++;
		}
		if (!tmp)
			ft_llstaddend(allst, new);
		else if (!(tmp->prev))
			ft_llstadd(allst, new);
		else
		{
			if (new)
			{
				ft_llstaddnode(&tmp, &new);
				(*allst)->size++;
			}
		}
	}
}
