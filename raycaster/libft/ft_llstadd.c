/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:12:01 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/15 18:59:59 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_llstadd(t_llist **allst, void const *content)
{
	t_node		*new;
	t_llist		*tmp;

	if ((tmp = *allst))
	{
		if ((new = (t_node*)malloc(sizeof(*new))))
		{
			new->content = ft_strdup(content);
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

