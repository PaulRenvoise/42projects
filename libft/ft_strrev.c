/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 18:28:12 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:36:15 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strrev(const char *s)
{
	char	*ret;
	int		i;
	int		n;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
		i++;
	n = i - 1;
	if (!(ret = (char*)malloc(sizeof(*ret) * (unsigned long)i)))
		return (NULL);
	while (i >= 0)
	{
		ret[n - i] = s[i];
		i--;
	}
	ret[n + 1] = '\0';
	return (ret);
}

