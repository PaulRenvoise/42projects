/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:06:48 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

int			seek_pipe(t_cmd_tree *root)
{
	if (root)
	{
		if (seek_pipe(root->left))
			return (1);
		if (root->type == PIPE)
			return (1);
		if (seek_pipe(root->right))
			return (1);
	}
	return (0);
}

int			seek_in_list(t_list *list, t_token *tk)
{
	while (list)
	{
		if (ft_strcmp(get_tk(list)->text, tk->text) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}
