/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstaddend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 18:05:59 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/05 17:32:35 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_cllstaddend(t_node **root, void const *content)
{
	t_node		*new;

	if (*root)
	{
		if ((new = (t_node*)malloc(sizeof(*new))))
		{
			new->content = ft_strdup(content);
			new->prev = (*root)->prev;
			new->next = (*root);
			(*root)->prev->next = new;
			(*root)->prev = new;
		}
	}
}
