/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bnew_or_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 14:23:14 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/23 12:10:24 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_bnew_or_add(t_btree **abtree, void *data, size_t size, int side)
{
	if (!*abtree)
		*abtree = ft_bnew(data, size);
	else
		ft_badd(abtree, data, size, side);
}
