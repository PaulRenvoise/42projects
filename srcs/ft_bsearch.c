/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsearch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 14:21:08 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:31:32 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void		*ft_bsearch(t_btree *abtree, void const *content)
{
	while (abtree)
	{
		if (!ft_strcmp(content, abtree->content))
			return (abtree->content);
		if (ft_strcmp(content, abtree->content) > 0)
			abtree = abtree->right;
		else
			abtree = abtree->left;
	}
	return (NULL);
}
