/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <ypringau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:36:14 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 11:30:40 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

void		*ft_memalloc(size_t size)
{
	void	*str;

	str = (void *)malloc(size * sizeof(void));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
