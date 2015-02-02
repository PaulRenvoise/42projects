/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 11:55:36 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/13 15:10:34 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>

void		next_inv(t_player *player, char *msg)
{
	if (player->inventory[3] >= 0)
		sprintf(msg + ft_strlen(msg), "sibur %d, ", player->inventory[3]);
	if (player->inventory[4] >= 0)
		sprintf(msg + ft_strlen(msg), "mendiane %d, ", player->inventory[4]);
	if (player->inventory[5] >= 0)
		sprintf(msg + ft_strlen(msg), "phiras %d, ", player->inventory[5]);
	if (player->inventory[6] >= 0)
		sprintf(msg + ft_strlen(msg), "thystame %d ", player->inventory[6]);
}

void		inventory(t_player *player, t_env *e, t_net *net)
{
	char	msg[BUF_SIZE + 1];

	ft_bzero(msg, BUF_SIZE + 1);
	if (ft_strcmp(net->fds[player->id].buf_read, "inventaire\n") == 0)
	{
		ft_strcpy(msg, "{ ");
		if (player->inventory[0] >= 0)
			sprintf(msg + ft_strlen(msg), "nourriture %d, ",
					player->inventory[0]);
		if (player->inventory[1] >= 0)
			sprintf(msg + ft_strlen(msg), "linemate %d, ",
					player->inventory[1]);
		if (player->inventory[2] >= 0)
			sprintf(msg + ft_strlen(msg), "deraumere %d, ",
					player->inventory[2]);
		next_inv(player, msg);
		ft_strcat(msg, "}\n");
		ft_lstadd_or_create(e, msg, player->id, 1 / e->time);
	}
}
