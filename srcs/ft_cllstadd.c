/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 18:06:11 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:09:31 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_cllstadd(t_node **root, t_node *new)
{
	if (*root)
	{
		if (new)
		{
			new->prev = (*root);
			new->next = (*root)->next;
			(*root)->next->prev = new;
			(*root)->next = new;
		}
	}
}
