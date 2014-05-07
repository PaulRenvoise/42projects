/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 13:57:43 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/29 17:23:50 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstprint(t_list *alst)
{
	t_list		*tmp;

	tmp = alst;
	while (tmp)
	{
		ft_putstr(tmp->content);
		tmp = tmp->next;
	}
}
