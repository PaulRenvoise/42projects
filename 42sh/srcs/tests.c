/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 16:56:42 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 17:21:13 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

int			split(char c)
{
	if (c == ';' || c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}

int			quote(char c)
{
	if (c == '"' || c == '\'' || c == '`')
		return (1);
	return (0);
}

int			open_par(char c)
{
	if (c == '(' || c == '{' || c == '[')
		return (1);
	return (0);
}

int			close_par(char c)
{
	if (c == ')' || c == '}' || c == ']')
		return (1);
	return (0);
}

int			notonlyspace(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}
