/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 15:45:19 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/17 15:14:12 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_test_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (ft_test_char(s[i]))
		i++;
	str = ft_strsub(s, (unsigned int)i, (ft_strlen(s) - (size_t)i));
	i = 0;
	while (str[j])
	{
		if (ft_test_char(str[j]))
			i++;
		if (!ft_test_char(str[j]) && str[j + 1])
			i = 0;
		j++;
	}
	str[ft_strlen(str) - (size_t)i] = '\0';
	return (str);
}
