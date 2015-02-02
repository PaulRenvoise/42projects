/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstaddend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:11:30 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/05 17:30:44 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_llstaddend(t_llist **allst, void const *content)
{
	t_node		*new;
	t_llist		*tmp;

	if ((tmp = *allst))
	{
		if ((new = (t_node*)malloc(sizeof(*new))))
		{
			new->content = ft_strdup(content);
			new->next = NULL;
			if (!(tmp->tail))
			{
				new->prev = NULL;
				tmp->head = new;
				tmp->tail = new;
			}
			else
			{
				tmp->tail->next = new;
				new->prev = tmp->tail;
				tmp->tail = new;
			}
			tmp->size++;
		}
	}
}

