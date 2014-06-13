/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 16:50:04 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 15:21:54 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (!ptr)
		return ((void*)malloc(size));
	if (!size)
		return (ptr);
	if ((new = (void*)malloc(size)))
		ft_memcpy(new, ptr, size);
	return (new);
}
