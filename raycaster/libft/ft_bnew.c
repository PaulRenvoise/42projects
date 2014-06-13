/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 14:23:50 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/23 12:11:00 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_btree			*ft_bnew(void *data, size_t size)
{
	t_btree		*new;

	if (!(new = (t_btree*)malloc(sizeof(*new))))
		return (NULL);
	if (!data)
	{
		new->data = NULL;
		new->size = 0;
	}
	else
	{
		if (!(new->data = (void*)malloc(size)))
			return (NULL);
		ft_memcpy(new->data, data, size);
		new->size = size;
	}
	new->left = NULL;
	new->right = NULL;
	return (new);
}
