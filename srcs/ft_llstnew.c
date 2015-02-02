/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:11:03 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:28:00 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_llist			*ft_llstnew(void)
{
	t_llist		*new;

	new = NULL;
	if ((new = (t_llist*)malloc(sizeof(*new))))
	{
		new->size = 0;
		new->head = NULL;
		new->tail = NULL;
	}
	return (new);
}
