/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 10:52:06 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:08:11 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

static int		egg_free(t_env *e, t_net *net, t_pos *pos, char *team)
{
	t_list	*list;

	list = e->eggs;
	while (list)
	{
		if (ft_strcmp(((t_egg *)(list->content))->team, team) == 0
				&& ((t_egg *)(list->content))->hatched == 1)
		{
			pos->x = ((t_egg *)(list->content))->x;
			pos->y = ((t_egg *)(list->content))->y;
			dprintf(net->fd_graphic, "ebo #%d\n",
					((t_egg *)(list->content))->id);
			del_elem_list(&e->eggs, list);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

void			add_player(t_env *e, t_net *net, int *add, int cs)
{
	t_player	*player;
	t_pos		pos;

	pos.x = -1;
	pos.y = -1;
	*add = 0;
	sprintf(net->fds[cs].buf_write, "%d\n",
			((t_team *)(e->teams->content))->max);
	if (egg_free(e, net, &pos, ((t_team *)(e->teams->content))->name)
			|| ((t_team *)(e->teams->content))->max > 0)
	{
		player = new_player(e, net->fds[cs].buf_read, &pos, cs);
		if (((t_team *)(e->teams->content))->players == NULL)
			((t_team *)(e->teams->content))->players =
				ft_lstnew(player, sizeof(t_player));
		else
			ft_lstadd_end(&((t_team *)(e->teams->content))->players,
					ft_lstnew(player, sizeof(t_player)));
		((t_team *)(e->teams->content))->max -= 1;
		dprintf(net->fd_graphic, "pnw #%d %d %d %d %d %s\n", cs, player->x,
				player->y, player->orientation, player->level, player->team);
		sprintf(net->fds[cs].buf_write + ft_strlen(net->fds[cs].buf_write),
				"%d %d\n", e->width, e->height);
		*add = 1;
	}
}

void			create_player(t_env *e, t_net *net, int cs)
{
	int			i;
	t_list		*head;
	int			add;

	add = -1;
	head = e->teams;
	i = 0;
	net->fds[cs].buf_read[ft_strlen(net->fds[cs].buf_read) - 1] = '\0';
	while (e->teams)
	{
		if (ft_strcmp(((t_team *)(e->teams->content))->name,
					net->fds[cs].buf_read) == 0)
			add_player(e, net, &add, cs);
		e->teams = e->teams->next;
	}
	e->teams = head;
	if (add == -1)
		dprintf(cs, "ko\n");
}
