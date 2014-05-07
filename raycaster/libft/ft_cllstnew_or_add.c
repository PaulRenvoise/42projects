/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstnew_or_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 13:45:39 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/29 17:25:37 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_cllstnew_or_add(t_node **root, void const *content, int call)
{
	if (!(*root))
		(*root) = ft_cllstnew();
	if (*root && call)
		ft_cllstaddend(root, content);
	else if (*root && !call)
		ft_cllstadd(root, content);
}
