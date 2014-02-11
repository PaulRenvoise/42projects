/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstquicksort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 17:30:38 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/16 17:31:49 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_lstquickswap(t_quickswap *swap)
{
		swap->tmp2 = (swap->tmp)->next;
		if (ft_strcmp((swap->tmp)->content, (swap->axe)->content) > 0)
		{
			(swap->tmp)->next = swap->next;
			swap->next = swap->tmp;
		}
		else
		{
			(swap->tmp)->next = swap->prev;
			swap->prev = swap->tmp;
		}
		swap->tmp = swap->tmp2;
}

t_list			*ft_lstquicksort(t_list *alst, t_list *end)
{
	t_quickswap	swap;

	if (alst != end && alst->next != end)
	{
		swap.axe = alst;
		swap.prev = swap.axe;
		swap.next = end;
		swap.tmp = alst->next;
		while (swap.tmp != end)
				ft_lstquickswap(&swap);
		swap.prev = ft_lstquicksort(swap.prev, swap.axe);
		swap.next = ft_lstquicksort(swap.next, end);
		swap.axe->next = swap.next;
		return (swap.prev);
	}
	return (alst);
}
