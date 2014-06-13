/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 12:41:08 by prenvois          #+#    #+#             */
/*   Updated: 2014/02/04 14:49:28 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

#define SPEC "dicsuoxp%"

/*
** Check if there is 'o', 'x', 'p' or '%' specifier. For each case,
** calls the appropriate function and assign the return value to "ret".
*/

static void		check_spec2(const char *format, int *i, va_list ap, size_t *ret)
{
	t_opts		ops;

	if (format[*i] == SPEC[4])
	{
		ops.u = va_arg(ap, unsigned int);
		write(1, ft_uitoa(ops.u), (*ret = ft_strlen(ft_uitoa(ops.u))));
	}
	else if (format[*i] == SPEC[5])
	{
		ops.o = va_arg(ap, unsigned int);
		write(1, ft_uitooa(ops.o), (*ret = ft_strlen(ft_uitooa(ops.o))));
	}
	else if (format[*i] == SPEC[6])
	{
		ops.x = va_arg(ap, unsigned int);
		write(1, ft_uitoxa(ops.x), (*ret = ft_strlen(ft_uitoxa(ops.x))));
	}
	else if (format[*i] == SPEC[7])
	{
		ops.p = va_arg(ap, long unsigned int);
		write(1, ft_luitoxa(ops.p), (*ret = ft_strlen(ft_luitoxa(ops.p))));
	}
	else if (format[*i] == SPEC[8])
		write(1, "%", (*ret = 1));
}

/*
** Check if there is 'd', 'i', 'c' or 's' specifier. For each case,
** calls the appropriate function and assign the return value to "ret".
** If there is no such spec, call the second checker.
*/

static void		check_spec(const char *format, int *i, va_list ap, size_t *ret)
{
	t_opts		ops;

	if (format[*i] == SPEC[0] || format[*i] == SPEC[1])
	{
		ops.d = va_arg(ap, int);
		write(1, ft_itoa(ops.d), (*ret = ft_strlen(ft_itoa(ops.d))));
	}
	else if (format[*i] == SPEC[2])
	{
		ops.c = (char)va_arg(ap, int);
		write(1, &ops.c, (*ret = 1));
	}
	else if (format[*i] == SPEC[3])
	{
		if ((ops.s = va_arg(ap, char*)))
			write(1, ops.s, (*ret = ft_strlen(ops.s)));
		else
			write(1, "(null)", (*ret = 6));
	}
	else
		check_spec2(format, i, ap, ret);
}

/*
** Parse the string given by ft_printf() by seeking the conversion's
** specificator and calling the specificator checker.
*/

static void		parser(const char *format, int *i, va_list ap, size_t *ret)
{
	while (!ft_strchr(SPEC, format[*i]) && !ft_isalpha(format[*i])
			&& format[*i])
		*i += 1;
	if (ft_strchr(SPEC, format[*i]))
	{
		check_spec(format, i, ap, ret);
		*i += 1;
	}
}

/*
** The function itself. Since it receive a variable argument's quantity,
** we use stdarg. Calls the parser if there's a '%' in the string, else,
** write the string on stdout. Return the number of caracters printed.
*/

int				ft_printf(const char *format, ...)
{
	int			i;
	size_t		c;
	size_t		ret;
	va_list		ap;

	i = 0;
	c = 0;
	ret = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			parser(format, &i, ap, &ret);
		}
		else
		{
			write(1, &(format[i++]), 1);
			c++;
		}
	}
	ret += c;
	va_end(ap);
	return ((int)ret);
}
