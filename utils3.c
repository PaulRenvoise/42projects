/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 19:24:36 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/19 18:53:38 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <stdlib.h>
#include <fcntl.h>

void			rand_color(t_env *e)
{
	static int	call = 0;

	if (!call)
	{
		e->c.wr += 5;
		e->c.wg += 2;
		e->c.wb += 7;
		if (e->c.wr > 255 && e->c.wb > 255)
			call = 1;
	}
	if (call)
	{
		e->c.wr -= 7;
		e->c.wg -= 5;
		e->c.wb -= 2;
		if (e->c.wg < 0)
			call = 0;
	}
}

void			stock_map(t_env *e)
{
	int			i;
	int			fd;
	char		*line;

	i = 0;
	line = NULL;
	if ((e->map = (int**)malloc(sizeof(int**) * 24)))
	{
		if ((fd = open("maps/demo", O_RDONLY)) != -1)
		{
			while (get_next_line(fd, &line) > 0)
			{
				if (line)
					e->map[i] = ft_strsplittoi(line, ' ');
				i++;
			}
		}
		else
		{
			ft_putendl_fd("Map file may be corrupted.", 2);
			exit(EXIT_FAILURE);
		}
	}
}

void			set_music(char ***tab)
{
	if (((*tab) = (char**)malloc(sizeof(char**) * 4)))
	{
		if (((*tab)[0] = (char*)malloc(sizeof(char*) * 21)))
			(*tab)[0] = "/usr/local/bin/mpg123";
		if (((*tab)[1] = (char*)malloc(sizeof(char*) * 2)))
			(*tab)[1] = "-q";
		if (((*tab)[2] = (char*)malloc(sizeof(char*) * 27)))
			(*tab)[2] = "./sounds/exploringcadet.mp3";
		(*tab)[3] = NULL;
	}
}
