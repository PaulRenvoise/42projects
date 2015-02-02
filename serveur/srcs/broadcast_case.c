/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 14:14:00 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/23 15:23:24 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>

int					casematch1(t_player *player)
{
	if (player->orientation == NORD)
		return (1);
	if (player->orientation == SUD)
		return (5);
	if (player->orientation == OUEST)
		return (7);
	if (player->orientation == EST)
		return (3);
	return (0);
}

int					casematch2(t_player *player)
{
	if (player->orientation == NORD)
		return (5);
	if (player->orientation == SUD)
		return (1);
	if (player->orientation == OUEST)
		return (3);
	if (player->orientation == EST)
		return (7);
	return (0);
}

int					casematch3(t_player *player)
{
	if (player->orientation == NORD)
		return (7);
	if (player->orientation == SUD)
		return (3);
	if (player->orientation == OUEST)
		return (5);
	if (player->orientation == EST)
		return (1);
	return (0);
}

int					casematch4(t_player *player)
{
	if (player->orientation == NORD)
		return (3);
	if (player->orientation == SUD)
		return (7);
	if (player->orientation == OUEST)
		return (1);
	if (player->orientation == EST)
		return (5);
	return (0);
}
