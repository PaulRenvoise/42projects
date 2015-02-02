/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <ypringau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:14:21 by ypringau          #+#    #+#             */
/*   Updated: 2014/01/31 12:22:34 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_strrchr(const char *s, int c)
{
	char	*match;
	int		i;

	match = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			match = (char *)&(s[i]);
		i++;
	}
	return (match);
}
