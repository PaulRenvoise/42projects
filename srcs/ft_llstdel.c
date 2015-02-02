/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 18:41:35 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:46:03 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_llstdel(t_llist **allst, t_node **node)
{
	if (*node && *allst)
	{
		if ((*node)->next == NULL)
		{
			(*allst)->tail = (*node)->prev;
			(*allst)->tail->next = NULL;
		}
		else if ((*node)->prev == NULL)
		{
			(*allst)->head = (*node)->next;
			(*allst)->head->prev = NULL;
		}
		else
		{
			(*node)->next->prev = (*node)->prev;
			(*node)->prev->next = (*node)->next;
		}
		free(*node);
		(*allst)->size--;
	}
}
