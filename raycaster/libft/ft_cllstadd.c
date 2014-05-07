/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 18:06:11 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/15 18:44:42 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_cllstadd(t_node **root, void const *content)
{
	t_node		*new;

	if (*root)
	{
		if ((new = (t_node*)malloc(sizeof(*new))))
		{
			new->content = ft_strdup(content);
			new->prev = (*root);
			new->next = (*root)->next;
			(*root)->next->prev = new;
			(*root)->next = new;
		}
	}
}
