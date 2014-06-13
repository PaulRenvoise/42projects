/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 15:53:06 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/27 19:21:25 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

int				builtin_jobs(t_env *e, int fd)
{
	int			i;
	t_list		*list;

	(void)fd;
	i = 1;
	list = e->jobs;
	while (list)
	{
		if (!(e->av[1]) || (e->av[1][0] == '%' && ft_atoi(&(e->av[1][1])) == i))
			ft_printf_fd("[%d] suspended %s\n", fd, i,
							((t_job *)(list->content))->str);
		list = list->next;
		i++;
	}
	return (1);
}
