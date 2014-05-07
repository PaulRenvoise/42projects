/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 17:11:34 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:37:34 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*str1;
	char	*str2;
	size_t	n;
	size_t	len;

	str1 = (char*)dst;
	str2 = (char*)src;
	n = size;
	while (n-- != 0 && *str1 != '\0')
		str1++;
	len = (size_t)(str1 - dst);
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(str2));
	while (*str2 != '\0')
	{
		if (n != 1)
		{
			*str1++ = *str2;
			n--;
		}
		str2++;
	}
	str1[n - 1] = '\0';
	return (len + (size_t)(str2 - src));
}
