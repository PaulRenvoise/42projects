/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revcase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/30 12:04:34 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/22 14:56:27 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_revcase(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!(str = (char*)s))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] <= 122 && str[i] >= 97)
			str[i] = str[i] - 32;
		else if (str[i] <= 90 && str[i] >= 65)
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}
