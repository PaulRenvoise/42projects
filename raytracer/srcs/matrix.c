/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 15:42:17 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 19:42:44 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <stdlib.h>
#include <math.h>

double			*trans_matrix(double *m)
{
	double	*res;

	res = (double *)malloc(sizeof(double) * 16);
	res[0] = m[0];
	res[1] = m[4];
	res[2] = m[8];
	res[3] = m[12];
	res[4] = m[1];
	res[5] = m[5];
	res[6] = m[9];
	res[7] = m[13];
	res[8] = m[2];
	res[9] = m[6];
	res[10] = m[10];
	res[11] = m[14];
	res[12] = m[3];
	res[13] = m[7];
	res[14] = m[11];
	res[15] = m[15];
	free(m);
	return (res);
}

void			m4_submat(double *m4, double **m3, int i, int j)
{
	t_pos	t;
	t_pos	dst;

	t.x = 0;
	while (t.x < 4)
	{
		t.y = 0;
		if (t.x < i)
			dst.x = t.x;
		else if (t.x > i)
			dst.x = t.x - 1;
		while (t.y < 4)
		{
			if (t.y < j)
				dst.y = t.y;
			else if (t.y > j)
				dst.y = t.y - 1;
			if (t.x != i && t.y != j)
				(*m3)[(dst.x * 3) + dst.y] = m4[(t.x * 4) + t.y];
			t.y++;
		}
		t.x++;
	}
}

double			m3_det(double *mat)
{
	return (mat[0] * ((mat[4] * mat[8]) - (mat[7] * mat[5]))
	- mat[1] * ((mat[3] * mat[8]) - (mat[6] * mat[5]))
	+ mat[2] * ((mat[3] * mat[7]) - (mat[6] * mat[4])));
}

double			m4_det(double *matrix)
{
	double	det;
	double	result;
	double	i;
	double	*m3;
	int		n;

	result = 0;
	i = 1;
	n = 0;
	m3 = (double *)malloc(sizeof(double) * 10);
	while (n < 4)
	{
		m4_submat(matrix, &m3, 0, n);
		det = m3_det(m3);
		result += matrix[n] * det * i;
		i *= -1;
		n++;
	}
	free(m3);
	return (result);
}

double			*invert_matrix(double *matrix)
{
	double	*inv_matrix;
	double	*mtmp;
	double	det;
	t_pos	pos;
	int		sign;

	pos.x = 0;
	inv_matrix = (double *)malloc(sizeof(double) * 16);
	mtmp = (double *)malloc(sizeof(double) * 10);
	det = m4_det(matrix);
	while (pos.x < 4)
	{
		pos.y = 0;
		while (pos.y < 4)
		{
			sign = 1 - ((pos.x + pos.y) % 2) * 2;
			m4_submat(matrix, &mtmp, pos.x, pos.y);
			inv_matrix[pos.x + pos.y * 4] = (m3_det(mtmp) * sign) / det;
			pos.y++;
		}
		pos.x++;
	}
	free(mtmp);
	free(matrix);
	return (inv_matrix);
}
