/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_k.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbrieuc <rbrieuc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 15:31:51 by rbrieuc           #+#    #+#             */
/*   Updated: 2014/06/23 15:35:08 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <stdio.h>
#include <stdlib.h>

static int	get_k_next_1(t_env *e, t_player *player, t_player *client)
{
	int	distx;
	int	disty;

	distx = abs(client->x - player->x);
	disty = abs(client->y - player->y);
	if (player->y > client->y && disty > e->height / 2)
		return (casematch2(client));
	if (player->y > client->y)
		return (casematch1(client));
	if (player->y < client->y && disty > e->height / 2)
		return (casematch1(client));
	if (player->y < client->y)
		return (casematch2(client));
	return (0);
}

static int	get_k_next_2(t_env *e, t_player *player, t_player *client)
{
	int	distx;
	int	disty;

	distx = abs(client->x - player->x);
	disty = abs(client->y - player->y);
	if (player->x > client->x && distx > e->width / 2)
		return (casematch4(client));
	if (player->x > client->x)
		return (casematch3(client));
	if (player->x < client->x && distx > e->width / 2)
		return (casematch3(client));
	if (player->x < client->x)
		return (casematch4(client));
	return (0);
}

static int	get_k_next_3(t_env *e, t_player *player, t_player *client)
{
	int	distx;
	int	disty;

	distx = abs(client->x - player->x);
	disty = abs(client->y - player->y);
	if (player->y > client->y && disty > e->height / 2
			&& distx > e->width / 2)
		return (casematch6(client));
	if (player->y > client->y && disty > e->height / 2)
		return (casematch8(client));
	if (player->y > client->y && distx > e->width / 2)
		return (casematch7(client));
	if (player->y > client->y)
		return (casematch5(client));
	if (player->y < client->y && disty > e->height / 2
			&& distx > e->width / 2)
		return (casematch7(client));
	if (player->y < client->y && disty > e->height / 2)
		return (casematch5(client));
	if (player->y < client->y && distx > e->width / 2)
		return (casematch6(client));
	if (player->y < client->y)
		return (casematch8(client));
	return (0);
}

static int	get_k_next_4(t_env *e, t_player *player, t_player *client)
{
	int	distx;
	int	disty;

	distx = abs(client->x - player->x);
	disty = abs(client->y - player->y);
	if (player->y > client->y && disty > e->height / 2
			&& distx > e->width / 2)
		return (casematch8(client));
	if (player->y > client->y && disty > e->height / 2)
		return (casematch6(client));
	if (player->y > client->y && distx > e->width / 2)
		return (casematch5(client));
	if (player->y > client->y)
		return (casematch7(client));
	if (player->y < client->y && disty > e->height / 2
			&& distx > e->width / 2)
		return (casematch5(client));
	if (player->y < client->y && disty > e->height / 2)
		return (casematch7(client));
	if (player->y < client->y && distx > e->width / 2)
		return (casematch8(client));
	if (player->y < client->y)
		return (casematch6(client));
	return (0);
}

int			get_k(t_env *e, t_player *player, t_player *client)
{
	int	distx;
	int	disty;

	distx = abs(client->x - player->x);
	disty = abs(client->y - player->y);
	if (player->x == client->x && player->y == client->y)
		return (0);
	if (player->x == client->x)
		return (get_k_next_1(e, player, client));
	if (player->y == client->y)
		return (get_k_next_2(e, player, client));
	if (player->x > client->x)
		return (get_k_next_3(e, player, client));
	if (player->x < client->x)
		return (get_k_next_4(e, player, client));
	return (0);
}
