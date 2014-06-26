/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 10:50:48 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:58:35 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>
#include <sys/time.h>

void	ft_lstadd_or_create(t_env *e, char *msg, int fd, float time)
{
	struct timeval	tv;
	unsigned long	newtime;

	gettimeofday(&tv, NULL);
	newtime = (1000000 * tv.tv_sec + tv.tv_usec) + (int)(1000000 * time);
	if (e->cmds == NULL)
		e->cmds = ft_lstnew(new_cmd(msg, fd, newtime), sizeof(t_cmd));
	else
	{
		ft_lstadd(&e->cmds, ft_lstnew(new_cmd(msg, fd, newtime),
			sizeof(t_cmd)));
	}
}

int		player_action(t_env *e, t_net *net, int cs)
{
	t_player	*player;

	player = get_player(e->teams, cs);
	if (player == NULL)
		return (-1);
	forward(player, e, net);
	right(player, e, net);
	left(player, e, net);
	broadcast(player, e, net);
	take(player, e, net);
	put(player, e, net);
	fork_client(player, e, net);
	connect_nbr(player, e, net);
	see(player, e, net);
	inventory(player, e, net);
	eject(player, e, net);
	incantation(player, e, net);
	return (1);
}
