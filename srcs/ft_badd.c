/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_badd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 14:22:20 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:32:23 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int				ft_badd(t_btree **abtree, t_btree *new, int side)
{
	t_btree		*tmp;
	t_btree		*prev;

	tmp = *abtree;
	prev = tmp;
	while (tmp)
	{
		prev = tmp;
		if (side)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	if (prev)
	{
		if (side)
			prev->left = new;
		else
			prev->right = new;
	}
	return (0);
}
