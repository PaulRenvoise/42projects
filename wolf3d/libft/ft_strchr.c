/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 17:07:37 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:34:29 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strchr(const char *s, int c)
{
	if (s[0] == (char)c)
		return ((char*)s);
	while (*s++)
	{
		if (*s == (char)c)
			return ((char*)s);
	}
	return (NULL);
}
