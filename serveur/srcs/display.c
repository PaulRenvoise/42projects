/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 13:16:57 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/19 12:18:08 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

void	display_list(t_list *list)
{
	t_list	*players;

	while (list)
	{
		printf("TEAM %s :\n", ((t_team *)(list->content))->name);
		printf("Players :\n");
		players = ((t_team *)(list->content))->players;
		if (players == NULL)
			printf("No player in this team\n");
		else
		{
			while (players)
			{
				printf("Player n %d :\n", ((t_player *)(players->content))->id);
				printf("Pos : %d %d\n", ((t_player *)(players->content))->x,
						((t_player *)(players->content))->y);
				printf("Or : %d\n",
						((t_player *)(players->content))->orientation);
				printf("Level : %d\n", ((t_player *)(players->content))->level);
				players = players->next;
			}
		}
		printf("-------------------------------------\n");
		list = list->next;
	}
}

void	display_map(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	while (i < e->height)
	{
		j = 0;
		while (j < e->width)
		{
			printf("%d %d %d %d %d %d %d | ", e->map[i][j][0], e->map[i][j][1],
				e->map[i][j][2], e->map[i][j][3], e->map[i][j][4],
				e->map[i][j][5], e->map[i][j][6]);
			j++;
		}
		printf("\n");
		i++;
	}
}
