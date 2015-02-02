/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstbblsort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:22:46 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:26:05 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstbblsort(t_list **alst)
{
	int		loop;
	t_list	*lst;

	loop = 1;
	while (loop)
	{
		loop = 0;
		lst = *alst;
		while (lst && lst->next)
		{
			if (ft_strcmp(lst->content, lst->next->content) > 0)
			{
				ft_lstswap(lst, lst->next);
				loop = 1;
			}
			lst = lst->next;
		}
	}
}
