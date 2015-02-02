/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstclr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 15:43:11 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:46:01 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_llstclr(t_llist **allst, t_node **node)
{
	t_node		*tmp;

	tmp = (*node);
	if (tmp != (*allst)->tail)
	{
		if (tmp->next)
			ft_llstclr(allst, &tmp->next);
		free(tmp->content);
		free(tmp);
		free((*allst));
		(*allst) = NULL;
	}
}
