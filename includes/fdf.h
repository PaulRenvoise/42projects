/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 16:46:11 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/22 16:38:59 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

# define WW 2560
# define WH 1440
# define TW 30
# define TH 30

typedef struct	s_coords
{
	int			x;
	int			y;
	int			z;
	int			w;
}				t_coords;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	char		*file;
	int			color;
	t_list		*lst;
}				t_env;

int			get_coords(t_env *env);
int			get_max_size(t_list *lstcoords);
#endif
