/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:58:49 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:32:52 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			ft_sqrt(double n)
{
	long		i;
	double		x;
	double		ret;
	const float	t = 1.5F;

	x = n * 0.5F;
	ret = n;
	i = * (long*) &ret;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	ret = * (double*) &i;
	ret = ret * (t - (x * ret * ret));
	ret = ret * (t - (x * ret * ret));
	return (1.0F / ret);
}
