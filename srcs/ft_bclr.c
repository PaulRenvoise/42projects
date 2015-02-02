/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bclr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 12:56:27 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:30:40 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_bclr(t_btree **abtree)
{
	t_btree		*tmp;

	tmp = NULL;
	if ((tmp = (*abtree)))
	{
		if (tmp->left)
			ft_bclr(&tmp->left);
		free(tmp->content);
		if (tmp->right)
			ft_bclr(&tmp->right);
		free(tmp);
		(*abtree) = NULL;
	}
}
