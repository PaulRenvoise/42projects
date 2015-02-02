/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:12:01 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/25 19:44:32 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_llstadd(t_llist **allst, t_node *new)
{
	t_llist		*tmp;

	if ((tmp = *allst))
	{
		if (new)
		{
			new->prev = NULL;
			if (!(tmp->tail))
			{
				new->next = NULL;
				tmp->head = new;
				tmp->tail = new;
			}
			else
			{
				tmp->head->prev = new;
				new->next = tmp->head;
				tmp->head = new;
			}
			tmp->size++;
		}
	}
}
