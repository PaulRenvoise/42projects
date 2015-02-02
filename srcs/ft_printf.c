/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 12:41:08 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 14:44:48 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#define SPEC "dicsuoxp%"

static void		check_spec3(const char *format, int *i, va_list ap, size_t *ret)
{
	char		*str;
	t_opts		ops;

	str = NULL;
	if (format[*i] == SPEC[6])
	{
		ops.x = va_arg(ap, unsigned int);
		str = ft_uitoxa(ops.x);
		write(1, str, (*ret = ft_strlen(str)));
		free(str);
	}
	else if (format[*i] == SPEC[7])
	{
		ops.p = va_arg(ap, long unsigned int);
		str = ft_luitoxa(ops.p);
		write(1, str, (*ret = ft_strlen(str)));
		free(str);
	}
	else if (format[*i] == SPEC[8])
		write(1, "%", (*ret = 1));
}

static void		check_spec2(const char *format, int *i, va_list ap, size_t *ret)
{
	char		*str;
	t_opts		ops;

	str = NULL;
	if (format[*i] == SPEC[4])
	{
		ops.u = va_arg(ap, unsigned int);
		str = ft_uitoa(ops.u);
		write(1, str, (*ret = ft_strlen(str)));
		free(str);
	}
	else if (format[*i] == SPEC[5])
	{
		ops.o = va_arg(ap, unsigned int);
		str = ft_uitooa(ops.o);
		write(1, str, (*ret = ft_strlen(str)));
		free(str);
	}
	else
		check_spec3(format, i, ap, ret);
}

static void		check_spec(const char *format, int *i, va_list ap, size_t *ret)
{
	char		*str;
	t_opts		ops;

	str = NULL;
	if (format[*i] == SPEC[0] || format[*i] == SPEC[1])
	{
		ops.d = va_arg(ap, int);
		str = ft_itoa(ops.d);
		write(1, str, (*ret = ft_strlen(str)));
		free(str);
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

static void		parser(const char *format, int *i, va_list ap, size_t *ret)
{
	while (!ft_strchr(SPEC, format[*i]) && !ft_isalpha(format[*i])
			&& format[*i])
		(*i)++;
	if (ft_strchr(SPEC, format[*i]))
	{
		check_spec(format, i, ap, ret);
		(*i)++;
	}
}

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
