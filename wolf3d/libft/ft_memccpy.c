/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:59:14 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/22 14:51:19 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void				*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	char			*dest;
	char			*src;
	unsigned char	w;

	dest = (char*)s1;
	src = (char*)s2;
	w = (unsigned char)c;
	if (n != 0)
	{
		while (n != 0)
		{
			if ((*dest++ = *src++) == w)
				return (dest);
			n--;
		}
	}
	return (NULL);
}
