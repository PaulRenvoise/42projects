/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsearch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 14:21:08 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/23 18:56:44 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void		*ft_bsearch(t_btree *abtree, void *data)
{
	while (abtree)
	{
		if (!ft_strcmp(data, abtree->data))
			return (abtree->data);
		if (ft_strcmp(data, abtree->data) > 0)
			abtree = abtree->right;
		else
			abtree = abtree->left;
	}
	return (NULL);
}
