/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbrieuc <rbrieuc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 16:03:29 by rbrieuc           #+#    #+#             */
/*   Updated: 2014/03/27 19:19:13 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

static void		no_option(int fd)
{
	int			i;
	int			j;
	t_dllist	*head;

	i = 1;
	head = get_termcap()->history;
	while (get_termcap()->history->next)
		(get_termcap()->history = get_termcap()->history->next);
	while (get_termcap()->history)
	{
		j = 0;
		while (j < (5 - (int)ft_strlen(ft_itoa(i))))
		{
			ft_putstr_fd(" ", fd);
			j++;
		}
		ft_printf_fd("%d  %s\n", fd, i, get_termcap()->history->content);
		(get_termcap()->history = get_termcap()->history->prev);
		i++;
	}
	get_termcap()->history = head;
}

static void		show_num(int i, int n, int fd)
{
	int			len;
	int			c;
	int			j;

	c = 0;
	while (get_termcap()->history->prev && c < n)
	{
		j = 0;
		len = (int)ft_strlen(ft_itoa(c + 1));
		if (n <= i)
			len = (int)ft_strlen(ft_itoa(i - n + c));
		while (j < (5 - len))
		{
			ft_putstr_fd(" ", fd);
			j++;
		}
		if (n <= i)
			ft_putnbr_fd(i - n + c, fd);
		else
			ft_putnbr_fd(c + 1, fd);
		ft_printf_fd("  %s\n", fd, get_termcap()->history->content);
		(get_termcap()->history = get_termcap()->history->prev);
		c++;
	}
}

static void		option_num(int n, int fd)
{
	int			i;
	int			k;
	t_dllist	*head;

	i = 1;
	k = 0;
	head = get_termcap()->history;
	while (get_termcap()->history->next)
	{
		(get_termcap()->history = get_termcap()->history->next);
		i++;
	}
	get_termcap()->history = head;
	while (get_termcap()->history->next && k < n)
	{
		(get_termcap()->history = get_termcap()->history->next);
		k++;
	}
	show_num(i, n, fd);
	get_termcap()->history = head;
}

static void		check_options(char *opts, char *arg)
{
	if (ft_strchr(opts, 'c'))
		option_c();
	if (ft_strchr(opts, 'd'))
		option_d(ft_atoi(arg));
	if (ft_strchr(opts, 'a') || ft_strchr(opts, 'w'))
		option_a(arg);
	if (ft_strchr(opts, 'r'))
		option_r(arg);
	if (ft_strchr(opts, 's') && arg)
		add_or_create_list_history(get_termcap(), arg);
}

int				builtin_history(t_env *e, int fd)
{
	int			i;

	if (e->av[1] == NULL)
		no_option(fd);
	else if (e->av[1][0] == '-')
	{
		i = 1;
		while (e->av[1][i] != '\0')
		{
			if (e->av[1][i] != 'c' && e->av[1][i] != 'd' && e->av[1][i] != 'a'
				&& e->av[1][i] != 'w' && e->av[1][i] != 'r'
				&& e->av[1][i] != 's')
			{
				ft_printf_fd("history: -%c: invalid option\n", 2, e->av[1][i]);
				ft_printf_fd("history: usage: history -c -d [offset] ", 2);
				ft_printf_fd("or history -awr [file] or history -s [arg]\n", 2);
				return (1);
			}
			i++;
		}
		check_options(e->av[1], e->av[2]);
	}
	else if (e->av[1])
		option_num(ft_atoi(e->av[1]), fd);
	return (1);
}
