/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 16:37:25 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/11 17:59:05 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <zappy.h>
#include <stdlib.h>
#include <time.h>

void	init(t_env *e)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	e->map = (int ***)malloc(sizeof(int **) * e->height);
	srand(time(0));
	while (i < e->height)
	{
		e->map[i] = (int **)malloc(sizeof(int *) * e->width);
		j = 0;
		while (j < e->width)
		{
			e->map[i][j] = (int *)malloc(sizeof(int) * 7);
			n = random_in_range(1, MAX_RESOURCE_TILE);
			while (n > 0)
			{
				e->map[i][j][random_in_range(0, 7)] += 1;
				n--;
			}
			j++;
		}
		i++;
	}
}

void	init_net(t_net *net)
{
	int				i;
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp) == -1)
		error("getrlimit");
	net->fd_graphic = 0;
	net->maxfd = rlp.rlim_cur;
	net->fds = (t_fd*)malloc(sizeof(*net->fds) * net->maxfd);
	i = 0;
	while (i < net->maxfd)
	{
		net->fds[i].type = FD_FREE;
		net->fds[i].fct_read = NULL;
		net->fds[i].fct_write = NULL;
		i++;
	}
}

void	init_fd(t_net *net)
{
	int	i;

	i = 0;
	net->max = 0;
	FD_ZERO(&net->fd_read);
	FD_ZERO(&net->fd_write);
	while (i < net->maxfd)
	{
		if (net->fds[i].type != FD_FREE)
		{
			FD_SET(i, &net->fd_read);
			if (ft_strlen(net->fds[i].buf_write) > 0)
				FD_SET(i, &net->fd_write);
			net->max = MAX(net->max, i);
		}
		i++;
	}
}

void	init_env(t_env *e)
{
	e->teams = NULL;
	e->cmds = NULL;
	e->eggs = NULL;
}
