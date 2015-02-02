/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 17:48:33 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:09:41 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>

void	check_fd(t_env *e, t_net *net)
{
	int	i;

	i = 0;
	while ((i < net->maxfd) && (net->r > 0))
	{
		if (FD_ISSET(i, &net->fd_read))
			net->fds[i].fct_read(e, net, i);
		if (FD_ISSET(i, &net->fd_write))
			net->fds[i].fct_write(e, net, i);
		if (FD_ISSET(i, &net->fd_read) ||
			FD_ISSET(i, &net->fd_write))
			net->r--;
		i++;
	}
}
