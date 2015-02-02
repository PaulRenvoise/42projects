/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 17:16:43 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:27:23 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_node			*ft_cllstnew(void const *content, size_t size)
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
		new->prev = new;
		new->next = new;
	}
	return (new);
}
