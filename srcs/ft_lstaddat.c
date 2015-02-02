/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 13:59:11 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:24:21 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstaddat(t_list **alst, t_list *new, size_t pos)
{
	t_list	*tmp;
	size_t	i;

	tmp = (*alst);
	if (tmp)
	{
		i = 0;
		while (tmp && i != pos)
		{
			tmp = tmp->next;
			i++;
		}
		if (!tmp)
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
