/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 14:08:22 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/29 17:24:21 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_llstprint(t_llist *allst)
{
	t_node		*tmp;

	if ((tmp = allst->head))
	{
		while (tmp)
		{
			ft_putstr(tmp->content);
			tmp = tmp->next;
		}
	}
}
