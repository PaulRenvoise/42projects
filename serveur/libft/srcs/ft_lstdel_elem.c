/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 19:29:09 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/06 19:30:05 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

void		ft_lstdel_elem(void *content, size_t content_size)
{
	if (content)
	{
		ft_bzero(content, content_size);
		free(content);
		content = NULL;
	}
}
