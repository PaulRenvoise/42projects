/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:36:25 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/22 15:12:54 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	y;

	if (!ft_strlen(s2))
		return ((char*)s1);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		if (s1[i] == s2[0])
		{
			y = 1;
			while (s2[y] == s1[i + y] && (y + i) < n)
				y++;
			if (s2[y] == '\0')
				return (&(((char*)s1)[i]));
		}
		i++;
	}
	return (NULL);
}
