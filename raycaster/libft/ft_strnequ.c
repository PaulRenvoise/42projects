/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 17:14:28 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/22 15:10:33 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i <= n)
	{
		i++;
		if (i == n || (s1[i] == '\0' && s2[i] == '\0'))
			return (1);
	}
	return (0);
}
