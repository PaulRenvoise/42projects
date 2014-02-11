/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstaddat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 13:38:07 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/05 17:32:08 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_cllstaddnew(t_node **root, t_node **new, void const *content)
{
	(*new)->content = ft_strdup(content);
	(*root)->next->prev = *new;
	(*root)->prev->next = *new;
	(*new)->prev = (*root)->prev;
	(*new)->next = (*root);
}

void			ft_cllstaddat(t_node **root, void const *content, size_t pos)
{
	t_node		*new;
	t_node		*tmp;
	size_t		i;

	if ((tmp = (*root)))
	{
		i = 0;
		while (tmp && i != pos)
		{
			tmp = tmp->next;
			i++;
		}
		if (!(tmp->next))
			ft_cllstaddend(root, content);
		else if (!(tmp->prev))
			ft_cllstadd(root, content);
		else
		{
			if ((new = (t_node*)malloc(sizeof(*new))))
				ft_cllstaddnew(root, &new, content);
		}
	}
}
