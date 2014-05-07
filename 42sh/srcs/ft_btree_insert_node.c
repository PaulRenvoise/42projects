/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 18:37:53 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 17:37:21 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

void				rotate_left(t_btree *t, t_btree_node *n)
{
	t_btree_node	*r;

	r = n->right;
	replace_node(t, n, r);
	n->right = r->left;
	if (r->left != NULL)
		r->left->parent = n;
	r->left = n;
	n->parent = r;
}

void				rotate_right(t_btree *t, t_btree_node *n)
{
	t_btree_node	*l;

	l = n->left;
	replace_node(t, n, l);
	n->left = l->right;
	if (l->right != NULL)
		l->right->parent = n;
	l->right = n;
	n->parent = l;
}

static int			next_utils(t_btree_node **node2, t_btree_node **node)
{
	if ((*node2)->right == NULL)
	{
		(*node2)->right = *node;
		return (2);
	}
	else
		(*node2) = (*node2)->right;
	return (0);
}

static int			next(t_item *item, t_btree_node **node,
					t_btree_node **node2, int cmp)
{
	if (cmp == 0)
	{
		((*node2)->item)->value = item->value;
		return (1);
	}
	else if (cmp < 0)
	{
		if ((*node2)->left == NULL)
		{
			(*node2)->left = *node;
			return (2);
		}
		else
			(*node2) = (*node2)->left;
	}
	else
	{
		if (next_utils(node2, node) == 2)
			return (2);
	}
	return (0);
}

void				ft_btree_insert_node(t_btree *t, t_item *item,
					int (*cmpf)(const char *, const char *))
{
	t_btree_node	*node;
	t_btree_node	*node2;
	int				cmp;
	int				ret;

	ret = 0;
	node = ft_btree_create_node(item, RED, NULL, NULL);
	if (t->root == NULL)
		t->root = node;
	else
	{
		node2 = t->root;
		while (1)
		{
			cmp = cmpf(item->name, (node2->item)->name);
			ret = next(item, &node, &node2, cmp);
			if (ret == 1)
				return ;
			else if (ret == 2)
				break ;
		}
		node->parent = node2;
	}
	insert_case1(t, node);
}
