/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bclr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 12:56:27 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/23 14:42:10 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_bclr(t_btree **abtree)
{
	t_btree		*tmp;

	tmp = *abtree;
	if (*abtree)
	{
		if (tmp->left)
			ft_bclr(&tmp->left);
		free(tmp);
		if (tmp->right)
			ft_bclr(&tmp->right);
		(*abtree) = NULL;
	}
}
