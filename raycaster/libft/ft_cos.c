/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 19:40:48 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:53:05 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_taylor_cos(double angle)
{
	int			step;
	double		fact;
	double		sq_angle;
	double		ret;

	sq_angle = angle * angle;
	angle = 1;
	step = 0;
	fact = 1;
	ret = 1;
	while (step++ < 10)
	{
		angle = angle * -1 * sq_angle;
		fact = fact * 2 * step * (2 * step - 1);
		ret = ret + angle / fact;
	}
	return (ret);
}

double			ft_cos(double angle)
{
	int			sign;
	double		pi;

	pi = 3.141592653589793;
	sign = 1;
	if (angle < 0)
		angle = -angle;
	if (!angle)
		return (1);
	else if (angle >= (pi / 2) && angle <= (pi / 2))
		return (0);
	else if (angle > (pi / 2))
	{
		angle = pi - angle;
		sign = -1;
	}
	return (sign * ft_taylor_cos(angle));
}
