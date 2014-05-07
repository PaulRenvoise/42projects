/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 17:07:17 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 13:07:38 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *s1, const char *s2)
{
	int		len;
	int		j;

	len = (int)ft_strlen(s1);
	j = 0;
	while (s2[j] != '\0')
		s1[len++] = s2[j++];
	s1[len] = '\0';
	return (s1);
}
