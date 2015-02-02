/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/10 19:29:07 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/22 14:43:00 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list				*ft_lstget(t_list *alst, unsigned int nbr)
{
	t_list			*lst;
	unsigned int	i;

	i = 1;
	lst = alst;
	while (i < nbr)
	{
		if (!lst)
			return (NULL);
		lst = lst->next;
		i++;
	}
	return (lst);
}
