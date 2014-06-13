/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/30 14:57:16 by prenvois          #+#    #+#             */
/*   Updated: 2013/11/30 15:15:16 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstswap(t_list *lst1, t_list *lst2)
{
	t_list	*tmp;
	size_t	size;

	size = sizeof(t_list) - sizeof(t_list*);
	ft_memcpy(&tmp, lst1, size);
	ft_memcpy(lst1, lst2, size);
	ft_memcpy(lst2, &tmp, size);
}
