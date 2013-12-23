/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 18:57:03 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/22 17:32:30 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_max_size(t_list *lstcoords)
{
	int			max;
	int			i;
	t_coords	*val;

	i = 0;
	max = 0;
	while (i < ft_lstsize(lstcoords))
	{
		val = ft_lstget(lstcoords, i)->content;
		if (max < val->z)
			max = val->z;
		i++;
	}
	return (max);
}

static int		close_win(int keycode, t_env *env)
{
	if (keycode == 65307)
	{
		mlx_clear_window(env->mlx, env->win);
		exit(0);
	}
	return (0);
}

static int		read_n_split(t_env *env)
{
	int			fd;
	int			ret;
	size_t		i;
	char		*line;

	i = 0;
	if ((fd = open(env->file, O_RDONLY)) == -1)
	{
		perror(env->file);
		return (1);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		i = 0;
		while (line[i])
		{
			if (ft_isalpha(line[i]) || (line[i] != ' ' && !ft_isdigit(line[i])))
				return (1);
			i++;
		}
		ft_lstnew_or_add(&env->lst, ft_lstsplit(line, ' '), sizeof(t_list), 1);
	}
	if (ret == -1)
		return (1);
	return (0);
}

int				main(int ac, char **av)
{
	t_env		env;

	if (ac == 2)
	{
		env.file = ft_strdup(av[1]);
		if (read_n_split(&env))
			return (1);
		if ((env.mlx = mlx_init()) == NULL)
			return (1);
		if ((env.win = mlx_new_window(env.mlx, WW, WH, "FDF")) == NULL)
			return (1);
		if (env.lst)
			mlx_expose_hook(env.win, get_coords, &env);
		mlx_key_hook(env.win, close_win, &env);
		mlx_loop(env.mlx);
		return (0);
	}
	else
	{
		ft_putstr_fd("usage : ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putendl_fd(" file1", 2);
	}
	return (1);
}
