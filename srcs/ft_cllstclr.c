/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstclr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 17:21:47 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:42:13 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_cllstclr(t_node **root)
{
	t_node	*tmp;
	t_node	*next;

	tmp = (*root)->next;
	while (tmp != (*root))
	{
		next = tmp->next;
		ft_cllstdel(tmp);
		tmp = next;
	}
}
