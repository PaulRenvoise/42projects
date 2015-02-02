/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstaddat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 13:38:07 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:28:32 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_cllstaddat(t_node **root, t_node *new, size_t pos)
{
	t_node		*tmp;
	size_t		i;

	if ((tmp = (*root)))
	{
		i = 0;
		while (tmp != (*root)->prev && i != pos)
		{
			tmp = tmp->next;
			i++;
		}
		if (tmp == (*root)->prev)
			ft_cllstaddend(root, new);
		else if (!(tmp->prev))
			ft_cllstadd(root, new);
		else
		{
			(*root)->next->prev = new;
			(*root)->prev->next = new;
			new->prev = (*root)->prev;
			new->next = (*root);
		}
	}
}
