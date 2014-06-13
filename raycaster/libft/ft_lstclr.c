/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 18:17:37 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/22 18:19:51 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_lstclr(t_list **alst)
{
	t_list		*tmp;

	tmp = (*alst)->next;
	while (*alst)
	{
		tmp = (*alst)->next;
		free(*alst);
		(*alst) = tmp;
	}
	free(*alst);
	(*alst) = NULL;
}
