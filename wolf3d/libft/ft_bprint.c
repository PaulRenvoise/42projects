/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 12:25:26 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/23 12:25:38 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_bprint(t_btree *abtree)
{
	if (abtree->left)
		ft_bprint(abtree->left);
	ft_putendl(abtree->data);
	if (abtree->right)
		ft_bprint(abtree->right);
}
