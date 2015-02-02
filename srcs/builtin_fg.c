/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 15:57:13 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/27 19:56:49 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <signal.h>
#include <sys/wait.h>

static int	put_err(char *info)
{
	ft_printf_fd("fg: %s: no such job\n", 2, info);
	return (1);
}

int			builtin_fg(t_env *e, int fd)
{
	int		i;
	int		ret;
	t_list	*list;

	(void)fd;
	i = 1;
	if ((list = e->jobs))
	{
		if (e->av[1] && e->av[1][0] == '%' && ft_atoi(&(e->av[1][1])) > 0)
		{
			while (list && i < ft_atoi(&(e->av[1][1])))
			{
				list = list->next;
				i++;
			}
			if (!list)
				return (put_err(e->av[1]));
		}
		reset_term(get_termcap(), 0);
		kill(((t_job *)(list->content))->pid, SIGCONT);
		waitpid(((t_job *)(list->content))->pid, &ret, WUNTRACED);
	}
	else
		ft_putendl_fd("fg: no current job", 2);
	return (1);
}
