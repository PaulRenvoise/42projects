/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 17:42:39 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:15:00 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <zappy.h>
#include <libft.h>

void	client_write(t_env *e, t_net *net, int cs)
{
	printf("SEND(%d) : %s\n", cs, net->fds[cs].buf_write);
	send(cs, net->fds[cs].buf_write, ft_strlen(net->fds[cs].buf_write), 0);
	if (ft_strstr(net->fds[cs].buf_write, "sendmap\n") != NULL)
		send_map(e, cs, 0);
	ft_bzero(net->fds[cs].buf_write, BUF_SIZE + 1);
}
