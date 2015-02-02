/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstnew_or_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:13:24 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 14:54:12 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_llstnew_or_add(t_llist **allst, void const *content, size_t size,
			int call)
{
	if (!*allst)
		*allst = ft_llstnew();
	if (*allst && call)
		ft_llstaddend(allst, ft_llstnewnode(content, size));
	else if (*allst && !call)
		ft_llstadd(allst, ft_llstnewnode(content, size));
}
