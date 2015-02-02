/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history_options.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbrieuc <rbrieuc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:19:17 by rbrieuc           #+#    #+#             */
/*   Updated: 2014/03/26 15:26:28 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <fcntl.h>
#include <unistd.h>

void			option_c(void)
{
	free_list_completion(&get_termcap()->history);
	get_termcap()->history = NULL;
	get_termcap()->head = NULL;
}

void			option_d(int n)
{
	int			i;
	t_dllist	*head;

	i = 0;
	head = get_termcap()->history;
	if (n == 1)
		head = get_termcap()->history->next;
	while (get_termcap()->history->next)
	{
		get_termcap()->history = get_termcap()->history->next;
		i++;
	}
	if (n > i || n == 0)
	{
		ft_printf_fd("history: %d:, history position out of range\n", 2, n);
		return ;
	}
	i = 1;
	while (i < n)
	{
		get_termcap()->history = get_termcap()->history->prev;
		i++;
	}
	ft_dllstdelitem(&get_termcap()->history);
	get_termcap()->history = head;
}

void			option_a(char *file)
{
	t_dllist	*head;

	if (!file)
	{
		file = ft_strdup("/.sh42.history");
		file = ft_strjoin(get_env()->home, file);
	}
	head = get_termcap()->history;
	write_list_reset(get_termcap(), file);
	get_termcap()->history = head;
}

void			option_r(char *file)
{
	int			fd;

	if (!file)
	{
		file = ft_strdup("/.sh42.history");
		file = ft_strjoin(get_env()->home, file);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	close(fd);
	write_list_init(get_termcap(), file, 0);
}
