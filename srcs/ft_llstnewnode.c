/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstnewnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 15:30:05 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:26:27 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_node			*ft_llstnewnode(void const *content, size_t size)
{
	t_node		*new;

	new = NULL;
	if ((new = (t_node*)malloc(sizeof(*new))))
	{
		if (!content)
			new->content = NULL;
		else
		{
			if (!(new->content = (void*)malloc(size)))
			{
				free(new);
				return (NULL);
			}
			ft_memcpy(new->content, content, size);
		}
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}
