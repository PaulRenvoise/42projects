/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstaddat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:13:49 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/05 17:31:19 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_llstaddnode(t_node **tmp, t_node **new, void const *content)
{
	(*new)->content = ft_strdup(content);
	(*tmp)->next->prev = *new;
	(*tmp)->prev->next = *new;
	(*new)->prev = (*tmp)->prev;
	(*new)->next = *tmp;
}

void		ft_llstaddat(t_llist **allst, void const *content, size_t pos)
{
	t_node	*new;
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
		if (!(tmp->next))
			ft_llstaddend(allst, content);
		else if (!(tmp->prev))
			ft_llstadd(allst, content);
		else
		{
			if ((new = (t_node*)malloc(sizeof(*new))))
			{
				ft_llstaddnode(&tmp, &new, content);
				(*allst)->size++;
			}
		}
	}
}
