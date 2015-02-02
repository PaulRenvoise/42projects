/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 13:57:43 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 15:32:06 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstprint(t_list *alst)
{
	t_list		*tmp;

	tmp = alst;
	while (tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}
