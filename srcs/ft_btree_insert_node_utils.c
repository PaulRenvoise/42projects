/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert_node_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 18:38:22 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 17:33:15 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

t_btree_node	*sibling(t_btree_node *n)
{
	if (n == n->parent->left)
		return (n->parent->right);
	else
		return (n->parent->left);
}

t_btree_node	*uncle(t_btree_node *n)
{
	return (sibling(n->parent));
}

t_btree_node	*grandparent(t_btree_node *n)
{
	return (n->parent->parent);
}

t_color			node_color(t_btree_node *n)
{
	t_color		color;

	color = (n == NULL ? BLACK : n->color);
	return (color);
}

void			replace_node(t_btree *t, t_btree_node *oldn,
				t_btree_node *newn)
{
	if (oldn->parent == NULL)
		t->root = newn;
	else
	{
		if (oldn == oldn->parent->left)
			oldn->parent->left = newn;
		else
			oldn->parent->right = newn;
	}
	if (newn != NULL)
		newn->parent = oldn->parent;
}
