/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 11:41:43 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:18:18 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t size)
{
	t_list	*new;

	new = NULL;
	if ((new = (t_list*)malloc(sizeof(*new))))
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
	}
	return (new);
}
