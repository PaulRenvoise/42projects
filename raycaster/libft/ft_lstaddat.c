/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 13:59:11 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/29 14:06:32 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstaddat(t_list **alst, t_list *new, size_t pos)
{
	t_list	*tmp;
	size_t	i;

	if ((tmp = *alst))
	{
		i = 0;
		while (tmp && i != pos)
		{
			tmp = tmp->next;
			i++;
		}
		if (!(tmp->next))
			ft_lstaddend(alst, new);
		else if (i == 0)
			ft_lstadd(alst, new);
		else
		{
			new->next = tmp->next->next;
			tmp->next = new;
		}
	}
}
