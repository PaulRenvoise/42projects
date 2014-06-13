/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 14:11:56 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/29 16:27:57 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strnchr(const char *s, int c)
{
	int		i;
	size_t	o;

	i = 0;
	o = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			o++;
		i++;
	}
	return (o);
}
