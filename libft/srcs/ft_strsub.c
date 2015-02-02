/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <ypringau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 17:35:17 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:38:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if (s)
	{
		i = 0;
		str = (char *)malloc(sizeof(char) * (len + 1));
		while (i < (start + len))
		{
			if (i >= start)
				str[i - start] = s[i];
			i++;
		}
		str[len] = '\0';
		return (str);
	}
	else
		return (NULL);
}
