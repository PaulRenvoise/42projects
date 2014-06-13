/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 11:24:16 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 14:55:13 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <stdlib.h>

t_coord			transf_point(t_coord point, double *matrix)
{
	t_coord	res;
	double	w;

	res.x = (point.x * matrix[0]) + (point.y * matrix[1])
		+ (point.z * matrix[2]) + matrix[3];
	res.y = (point.x * matrix[4]) + (point.y * matrix[5])
		+ (point.z * matrix[6]) + matrix[7];
	res.z = (point.x * matrix[8]) + (point.y * matrix[9])
		+ (point.z * matrix[10]) + matrix[11];
	w = (point.x * matrix[12]) + (point.y * matrix[13])
		+ (point.z * matrix[14]) + matrix[15];
	if (w != 1 && w != 0)
	{
		res.x /= w;
		res.y /= w;
		res.z /= w;
	}
	free(matrix);
	return (res);
}

t_coord			transf_vector(t_coord vector, double *matrix)
{
	t_coord	res;

	res.x = (vector.x * matrix[0]) + (vector.y * matrix[1])
		+ (vector.z * matrix[2]);
	res.y = (vector.x * matrix[4]) + (vector.y * matrix[5])
		+ (vector.z * matrix[6]);
	res.z = (vector.x * matrix[8]) + (vector.y * matrix[9])
		+ (vector.z * matrix[10]);
	res = normalize(res);
	free(matrix);
	return (res);
}

double			*cpy_matrix(double *matrix)
{
	double	*m;
	int		i;

	m = (double *)malloc(sizeof(double) * 16);
	i = 0;
	while (i < 16)
	{
		m[i] = matrix[i];
		i++;
	}
	return (m);
}

t_ray			transf_ray(t_ray ray, double *matrix)
{
	t_ray	tray;
	double	*matrix_save;

	matrix_save = cpy_matrix(matrix);
	tray.origin = transf_point(ray.origin, matrix);
	tray.vector = transf_vector(ray.vector, matrix_save);
	return (tray);
}
