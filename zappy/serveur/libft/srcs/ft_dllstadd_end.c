/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllstadd_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 11:27:55 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 11:27:58 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_dllstadd_end(t_dllist **alst, t_dllist *new)
{
	t_dllist	*root;

	root = *alst;
	while ((*alst)->next)
		*alst = (*alst)->next;
	new->prev = (*alst);
	(*alst)->next = new;
	*alst = root;
}
