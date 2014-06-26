/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 10:08:13 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 16:22:28 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <zappy.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>

static void	queue_cmd(t_env *e, t_net *net, unsigned long time)
{
	t_list	*head;

	head = e->cmds;
	while (e->cmds)
	{
		if (time >= ((t_cmd *)(e->cmds->content))->time)
		{
			ft_strcpy(net->fds[((t_cmd *)(e->cmds->content))->fd].buf_write
			+ ft_strlen(net->fds[((t_cmd *)(e->cmds->content))->fd].buf_write),
					((t_cmd *)(e->cmds->content))->msg);
			del_elem_list(&head, e->cmds);
		}
		e->cmds = e->cmds->next;
	}
	e->cmds = head;
}

int			main(int ac, char **av)
{
	t_env			e;
	t_net			net;
	struct timeval	tv;
	struct timeval	t;

	t.tv_sec = 0;
	t.tv_usec = 1000;
	if (ac < 13)
		usage(av);
	init_env(&e);
	parse_options(&e, av);
	init(&e);
	init_net(&net);
	srv_create(&net, e.port);
	while (42)
	{
		init_fd(&net);
		gettimeofday(&tv, NULL);
		net.r = select(net.max + 1, &net.fd_read, &net.fd_write, NULL, &t);
		queue_cmd(&e, &net, 1000000 * tv.tv_sec + tv.tv_usec);
		egg_hatching(&e, e.eggs, &net, 1000000 * tv.tv_sec + tv.tv_usec);
		lose_life(e.teams, &e, &net, 1000000 * tv.tv_sec + tv.tv_usec);
		check_fd(&e, &net);
	}
}
