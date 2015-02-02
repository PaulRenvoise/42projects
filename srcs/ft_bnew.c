/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 14:23:50 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:28:44 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_btree			*ft_bnew(void const *content, size_t size)
{
	t_btree		*new;

	new = NULL;
	if ((new = (t_btree*)malloc(sizeof(*new))))
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
		new->left = NULL;
		new->right = NULL;
	}
	return (new);
}
