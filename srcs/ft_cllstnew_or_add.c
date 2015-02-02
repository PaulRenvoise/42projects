/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstnew_or_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 13:45:39 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:11:26 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_cllstnew_or_add(t_node **root, void const *content, size_t size,
								int call)
{
	if (!(*root))
		(*root) = ft_cllstnew(content, size);
	else if (*root && call)
		ft_cllstaddend(root, ft_cllstnew(content, size));
	else if (*root && !call)
		ft_cllstadd(root, ft_cllstnew(content, size));
}
