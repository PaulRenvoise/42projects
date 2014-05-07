/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 15:01:22 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <termios.h>

struct termios	*get_termios(void)
{
	static struct termios	term;

	return (&term);
}

struct termios	*get_newterm(void)
{
	static struct termios	new_term;

	return (&new_term);
}

t_termcap		*get_termcap(void)
{
	static t_termcap	termcap;

	return (&termcap);
}

t_env			*get_env(void)
{
	static t_env	env;

	return (&env);
}
