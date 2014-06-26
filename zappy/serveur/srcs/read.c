/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 17:41:01 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:14:50 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <zappy.h>
#include <libft.h>
#include <stdlib.h>

static void	send_info_dc(t_env *e, t_net *net, int cs)
{
	close(cs);
	ft_bzero(net->fds[cs].buf_read, BUF_SIZE + 1);
	net->fds[cs].type = FD_FREE;
	net->fds[cs].fct_read = NULL;
	net->fds[cs].fct_write = NULL;
	delete_player(e->teams, cs);
	dprintf(net->fd_graphic, "pdi #%d\n", cs);
	display_list(e->teams);
	printf("Client #%d gone away\n", cs);
}

void		client_read(t_env *e, t_net *net, int cs)
{
	int	r;

	r = recv(cs, net->fds[cs].buf_read, BUF_SIZE, 0);
	printf("read : %s\n", net->fds[cs].buf_read);
	if (r <= 0)
		send_info_dc(e, net, cs);
	else
	{
		if (ft_strcmp(net->fds[cs].buf_read, "GRAPHIC\n") == 0)
			welcome(e, net, cs);
		else
		{
			if (net->fd_graphic != 0 && cs == net->fd_graphic)
				gfx_commands(e, net, cs);
			else if (player_action(e, net, cs) == -1)
				create_player(e, net, cs);
			display_list(e->teams);
		}
		ft_bzero(net->fds[cs].buf_read, BUF_SIZE + 1);
	}
}
