/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 19:42:45 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:53:06 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_taylor_sin(double angle)
{
	int			step;
	double		fact;
	double		sq_angle;
	double		ret;

	sq_angle = angle * angle;
	ret = angle;
	step = 0;
	fact = 1;
	while (step++ < 10)
	{
		angle = angle * -1 * sq_angle;
		fact = fact * 2 * step * (2 * step + 1);
		ret = ret + angle / fact;
	}
	return (ret);
}

double			ft_sin(double angle)
{
	int			sign;
	double		pi;

	pi = 3.141592653589793;
	sign = 1;
	if (angle < 0)
	{
		angle = -angle;
		sign = -1;
	}
	if (!angle)
		return (0);
	else if (angle >= (pi / 2) && angle <= (pi / 2))
		return (1);
	else if (angle > (pi / 2))
		angle = pi - angle;
	return (sign * ft_taylor_sin(angle));
}
