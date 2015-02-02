/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 17:11:31 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:49:42 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstdel(t_list **alst)
{
	t_list	*tmp;

	tmp = NULL;
	if (*alst)
	{
		tmp = (*alst)->next->next;
		free((*alst)->next);
		(*alst)->next = tmp;
	}
}
