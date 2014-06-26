/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 11:45:07 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:12:19 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

void		fork_client(t_player *player, t_env *e, t_net *net)
{
	char		msg[BUF_SIZE + 1];
	static int	id = 0;
	t_egg		*egg;

	ft_bzero(msg, BUF_SIZE + 1);
	if (ft_strcmp(net->fds[player->id].buf_read, "fork\n") == 0)
	{
		dprintf(net->fd_graphic, "pfk #%d\n", player->id);
		egg = new_egg(e, id, *player);
		if (e->eggs == NULL)
			e->eggs = ft_lstnew(egg, sizeof(t_egg));
		else
			ft_lstadd_end(&e->eggs, ft_lstnew(egg, sizeof(t_egg)));
		sprintf(msg, "enw #%d #%d %d %d\n", id, player->id,
				player->x, player->y);
		id++;
		ft_lstadd_or_create(e, msg, net->fd_graphic, 42 / e->time);
		ft_lstadd_or_create(e, "ok\n", player->id, 42 / e->time);
	}
}

void		connect_nbr(t_player *player, t_env *e, t_net *net)
{
	t_list	*list;

	if (ft_strcmp(net->fds[player->id].buf_read, "connect_nbr\n") == 0)
	{
		list = e->teams;
		while (list)
		{
			if (ft_strcmp(((t_team *)(list->content))->name, player->team) == 0)
			{
				sprintf(net->fds[player->id].buf_write
						+ ft_strlen(net->fds[player->id].buf_write), "%d\n",
						((t_team *)(list->content))->max);
				break ;
			}
			list = list->next;
		}
	}
}
