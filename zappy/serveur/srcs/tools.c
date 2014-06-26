/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 10:11:30 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/11 16:32:05 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zappy.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

void	usage(char **av)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(av[0], 2);
	ft_putstr_fd(" -p <port> -x <width> -y <height> -n <team> [<team>] ", 2);
	ft_putendl_fd("[<team>] ... -c <nb> -t <t>", 2);
	ft_putendl_fd("   -p numero de port", 2);
	ft_putendl_fd("   -x largeur du monde", 2);
	ft_putendl_fd("   -y hauteur du monde", 2);
	ft_putendl_fd("   -n nom_equipe_1 nom_equipe_2...", 2);
	ft_putendl_fd("   -c nombre de client autorises au commencement du jeu", 2);
	ft_putendl_fd("   -t diviseur de l'unite de temps", 2);
	exit(-1);
}

void	error(char *msg)
{
	fprintf(stderr, "Error with : %s\n", msg);
	exit(-1);
}

int		random_in_range(unsigned int min, unsigned int max)
{
	int	base_random;
	int	range;
	int	remainder;
	int	bucket;

	base_random = rand();
	if (RAND_MAX == base_random)
		return (random_in_range(min, max));
	range = max - min;
	remainder = RAND_MAX % range;
	bucket = RAND_MAX / range;
	if (base_random < RAND_MAX - remainder)
		return (min + base_random / bucket);
	else
		return (random_in_range (min, max));
}
