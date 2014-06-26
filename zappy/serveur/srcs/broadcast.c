/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 10:57:30 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:33:18 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>
#include <stdlib.h>

static void	send_message(t_env *e, t_player *player, t_player *client,
		char *message)
{
	char	msg[BUF_SIZE + 1];
	int		k;

	ft_bzero(msg, BUF_SIZE + 1);
	if (client->id != player->id)
	{
		k = get_k(e, player, client);
		printf("k : %d\n", k);
		sprintf(msg, "message %d, %s", k, message);
		ft_lstadd_or_create(e, msg, client->id, 7 / e->time);
	}
}

void		broadcast(t_player *player, t_env *e, t_net *net)
{
	char	**tab;
	t_list	*players;
	t_list	*list;

	if (ft_strncmp(net->fds[player->id].buf_read, "broadcast", 9) == 0)
	{
		tab = ft_strsplit(net->fds[player->id].buf_read, ' ');
		list = e->teams;
		while (list)
		{
			players = ((t_team *)(list->content))->players;
			while (players)
			{
				send_message(e, player, ((t_player *)(players->content)),
						tab[1]);
				players = players->next;
			}
			list = list->next;
		}
		dprintf(net->fd_graphic, "pbc #%d %s", player->id, tab[1]);
		ft_lstadd_or_create(e, "ok\n", player->id, 7 / e->time);
	}
}
