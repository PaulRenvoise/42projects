/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_or_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 14:31:42 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:02:53 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstnew_or_add(t_list **alst, void const *content, size_t size,
							int call)
{
	if (!*alst)
		*alst = ft_lstnew(content, size);
	else if (*alst && call)
		ft_lstaddend(alst, ft_lstnew(content, size));
	else if (*alst && !call)
		ft_lstadd(alst, ft_lstnew(content, size));
}
