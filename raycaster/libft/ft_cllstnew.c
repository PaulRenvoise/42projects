/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cllstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 17:16:43 by prenvois          #+#    #+#             */
/*   Updated: 2013/12/29 13:34:28 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_node			*ft_cllstnew(void)
{
	t_node		*root;

	root = NULL;
	if ((root = (t_node*)malloc(sizeof(*root))))
	{
		if ((root->content = (void*)malloc(4)))
			ft_memcpy(root->content, "ROOT", 4);
		root->prev = root;
		root->next = root;
	}
	return (root);
}
