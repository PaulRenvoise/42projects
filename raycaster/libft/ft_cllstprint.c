/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 17:41:31 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/29 13:19:52 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_cllstprint(t_node *root)
{
	t_node		*tmp;

	if ((tmp = root->next))
	{
		while (tmp != root)
		{
			ft_putstr(tmp->content);
			tmp = tmp->next;
		}
	}
}

