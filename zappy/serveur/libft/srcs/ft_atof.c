/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 20:04:36 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 11:26:45 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_atof.h>

static void		get_int(int num, t_atof *a)
{
	if (a->fraction == 1)
	{
		a->fraction_part = a->fraction_part * 10 + (num - '0');
		a->divisor *= 10;
	}
	else
		a->integer_part = a->integer_part * 10 + (num - '0');
}

static void		get_sign(char **num, t_atof *atof)
{
	if (**num == '-')
	{
		if (atof->sign == -1)
			atof->sign = 1;
		else
			atof->sign = -1;
		(*num)++;
	}
	else if (**num == '+')
		(*num)++;
}

static void		init_struct(t_atof *atof)
{
	atof->fraction = 0;
	atof->fraction_part = 0;
	atof->integer_part = 0;
	atof->divisor = 1;
	atof->sign = 1;
}

double			ft_atof(char *num)
{
	t_atof		a;
	int			i;

	i = 0;
	if (!num || !*num)
		return (0);
	init_struct(&a);
	get_sign(&num, &a);
	while (num[i] != '\0')
	{
		if (num[i] >= '0' && num[i] <= '9')
			get_int(num[i], &a);
		else if (num[i] == '.')
		{
			if (a.fraction)
				return (a.sign * (a.integer_part + a.fraction_part
				/ a.divisor));
			else
				a.fraction = 1;
		}
		else
			return (a.sign * (a.integer_part + a.fraction_part / a.divisor));
		i++;
	}
	return (a.sign * (a.integer_part + a.fraction_part / a.divisor));
}
