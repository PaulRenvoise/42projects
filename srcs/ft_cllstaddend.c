/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstaddend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 18:05:59 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:09:59 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_cllstaddend(t_node **root, t_node *new)
{
	if (*root)
	{
		if (new)
		{
			new->prev = (*root)->prev;
			new->next = (*root);
			(*root)->prev->next = new;
			(*root)->prev = new;
		}
	}
}
