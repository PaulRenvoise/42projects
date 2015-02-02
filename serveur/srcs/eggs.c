/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eggs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 10:40:44 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/13 11:08:01 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

static void	change_max(t_env *e, char *team, int var)
{
	t_list	*head_teams;

	head_teams = e->teams;
	while (e->teams)
	{
		if (ft_strcmp(((t_team *)(e->teams->content))->name, team) == 0)
		{
			if (var == -1)
				((t_team *)(e->teams->content))->max -= 1;
			else
				((t_team *)(e->teams->content))->max += 1;
		}
		e->teams = e->teams->next;
	}
	e->teams = head_teams;
}

void		egg_hatching(t_env *e, t_list *head, t_net *net, unsigned long time)
{
	while (e->eggs)
	{
		if (time >= ((t_egg *)(e->eggs->content))->time)
		{
			if (((t_egg *)(e->eggs->content))->hatched == 0)
			{
				((t_egg *)(e->eggs->content))->hatched = 1;
				((t_egg *)(e->eggs->content))->time +=
					(int)(1000000 * (1260 / e->time));
				dprintf(net->fd_graphic, "eht #%d\n",
						((t_egg *)e->eggs->content)->id);
				change_max(e, ((t_egg *)e->eggs->content)->team, +1);
			}
			else
			{
				dprintf(net->fd_graphic, "edi #%d\n",
						((t_egg *)e->eggs->content)->id);
				change_max(e, ((t_egg *)e->eggs->content)->team, -1);
				del_elem_list(&head, e->eggs);
			}
		}
		e->eggs = e->eggs->next;
	}
	e->eggs = head;
}
