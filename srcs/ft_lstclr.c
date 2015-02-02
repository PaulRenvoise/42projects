/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 18:17:37 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:48:46 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_lstclr(t_list **alst)
{
	t_list		*tmp;

	tmp = NULL;
	if ((tmp = (*alst)))
	{
		if (tmp->next)
			ft_lstclr(&tmp->next);
		free(tmp->content);
		free(tmp);
		(*alst) = NULL;
	}
}
