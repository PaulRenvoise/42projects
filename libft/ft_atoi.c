/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:23:26 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:36:09 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	num;
	int	neg;
	int	i;

	num = 0;
	i = 0;
	neg = 1;
	while (str[i] < 33)
		i++;
	if (str[i] == '-' || str[i] == '+')
		neg = (str[i++] == '+' ? 1 : -1);
	while (str[i] != '\0' && (str[i] > 47 && str[i] < 58))
		num = num * 10 + str[i++] - '0';
	return (neg * num);
}

