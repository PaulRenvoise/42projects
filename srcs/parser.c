/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 20:37:08 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 16:42:03 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <get_next_line.h>
#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

void			file_error(int type, char *info1, char *info2)
{
	if (type == 1)
		ft_putendl("Error: only camera, objects, lights are supported");
	else if (type == 2)
		ft_putendl("Error: must be '{' to begin a definition");
	else if (type == 3)
		ft_putendl("Error: must be '}' to end a definition");
	else if (type == 4)
	{
		ft_putstr("Error: ");
		ft_putstr(info1);
		ft_putstr(" is not a possible member of ");
		ft_putendl(info2);
	}
	else if (type == 5)
	{
		ft_putstr("Error: Too much arguments for a ");
		ft_putendl(info1);
	}
	else if (type == 6)
		ft_putendl("Error: position can only be double or int");
	else
		ft_putendl("Error: Error unknown");
	exit(0);
}

int				parse_item(int fd, t_env *e, char *line,
					int (*f)(t_env *, char *, int *, int fd))
{
	int		i;

	i = 0;
	if (line[0] != '\0')
	{
		if (f(e, line, &i, fd))
			return (1);
	}
	while (get_next_line(fd, &line) == 1)
	{
		line = ft_strtrim(line);
		if (f(e, line, &i, fd))
			return (1);
	}
	return (0);
}

static void		parser_check_item(char *line, t_env *e, int fd)
{
	line = ft_strtrim(line);
	if (ft_strncmp("camera", line, 6) == 0)
	{
		line = &(ft_strchr(line, ':'))[1];
		line = ft_strtrim(line);
		parse_item(fd, e, line, &parse_cam_line);
	}
	else if (ft_strncmp("objects", line, 7) == 0)
	{
		line = &(ft_strchr(line, ':'))[1];
		line = ft_strtrim(line);
		parse_item(fd, e, line, &parse_objects_line);
	}
	else if (ft_strncmp("lights", line, 6) == 0)
	{
		line = &(ft_strchr(line, ':'))[1];
		line = ft_strtrim(line);
		parse_item(fd, e, line, &parse_lights_line);
	}
	else
		file_error(1, NULL, NULL);
}

static void		parser(char *file, t_env *e)
{
	int			fd;
	char		*line;
	struct stat	sb;

	line = NULL;
	stat(file, &sb);
	if (S_ISDIR(sb.st_mode))
	{
		ft_putendl("Usage: ./raytracer [file.rt]");
		exit(0);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		exit(0);
	}
	while (get_next_line(fd, &line) == 1)
		parser_check_item(line, e, fd);
}

void			init_parser(t_env *e, int ac, char **av)
{
	if (ac != 2)
	{
		ft_putendl("Usage: ./raytracer [file.rt]");
		exit (0);
	}
	else
		parser(av[1], e);
}
