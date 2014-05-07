/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 15:06:03 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/11 15:29:14 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float		ft_atof(const char *str)
{
	float	res;
	float	sign;
	int		point;

	point = 0;
	res = 0;
	sign = 1;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	while (*str)
	{
		if (*str == '.')
			point = 1;
		if ((*str - '0') >= 0 && (*str - '0') <= 9)
		{
			if (point)
				sign = sign / 10.0;
			res = res * 10.0 + (float)(*str - '0');
		}
		str++;
	}
	return (res * sign);
}
