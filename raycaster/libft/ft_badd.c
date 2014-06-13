/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_badd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 14:22:20 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/23 12:12:51 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_baddnode(t_btree *prev, void *data, size_t size, int side)
{
	if (side)
		prev->left = ft_bnew(data, size);
	else
		prev->right = ft_bnew(data, size);
}

int				ft_badd(t_btree **abtree, void *data, size_t size, int side)
{
	t_btree		*tmp;
	t_btree		*prev;

	prev = NULL;
	tmp = *abtree;
	while (tmp)
	{
		prev = tmp;
		if (side)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	ft_baddnode(prev, data, size, side);
	return (0);
}
