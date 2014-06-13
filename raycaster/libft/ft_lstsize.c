/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/10 19:21:13 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/11 11:12:34 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstsize(t_list *alst)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = alst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
