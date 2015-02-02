/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 17:53:38 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/28 17:55:34 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_cllstdel(t_node *node)
{
	if (node)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);
	}
}
