/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast_case2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbrieuc <rbrieuc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 15:22:51 by rbrieuc           #+#    #+#             */
/*   Updated: 2014/06/23 15:23:23 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>

int					casematch5(t_player *player)
{
	if (player->orientation == NORD)
		return (8);
	if (player->orientation == SUD)
		return (4);
	if (player->orientation == OUEST)
		return (6);
	if (player->orientation == EST)
		return (2);
	return (0);
}

int					casematch6(t_player *player)
{
	if (player->orientation == NORD)
		return (4);
	if (player->orientation == SUD)
		return (8);
	if (player->orientation == OUEST)
		return (2);
	if (player->orientation == EST)
		return (6);
	return (0);
}

int					casematch7(t_player *player)
{
	if (player->orientation == NORD)
		return (2);
	if (player->orientation == SUD)
		return (6);
	if (player->orientation == OUEST)
		return (8);
	if (player->orientation == EST)
		return (4);
	return (0);
}

int					casematch8(t_player *player)
{
	if (player->orientation == NORD)
		return (6);
	if (player->orientation == SUD)
		return (2);
	if (player->orientation == OUEST)
		return (4);
	if (player->orientation == EST)
		return (8);
	return (0);
}
