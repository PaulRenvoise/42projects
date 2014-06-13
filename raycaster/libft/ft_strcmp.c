/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:52:33 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:34:16 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s2[i] != '\0')
		i++;
	if (s1[i] - s2[i] < 0)
		return (-1);
	else if (s1[i] - s2[i] > 0)
		return (1);
	else
		return (0);
}
