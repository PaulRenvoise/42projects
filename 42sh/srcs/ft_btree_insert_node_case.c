/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert_node_case.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 18:38:07 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

static void		insert_case5(t_btree *t, t_btree_node *n)
{
	n->parent->color = BLACK;
	grandparent(n)->color = RED;
	if (n == n->parent->left && n->parent == grandparent(n)->left)
		rotate_right(t, grandparent(n));
	else
		rotate_left(t, grandparent(n));
}

static void		insert_case4(t_btree *t, t_btree_node *n)
{
	if (n == n->parent->right && n->parent == grandparent(n)->left)
	{
		rotate_left(t, n->parent);
		n = n->left;
	}
	else if (n == n->parent->left && n->parent == grandparent(n)->right)
	{
		rotate_right(t, n->parent);
		n = n->right;
	}
	insert_case5(t, n);
}

static void		insert_case3(t_btree *t, t_btree_node *n)
{
	if (node_color(uncle(n)) == RED)
	{
		n->parent->color = BLACK;
		(uncle(n))->color = BLACK;
		(grandparent(n))->color = RED;
		insert_case1(t, grandparent(n));
	}
	else
		insert_case4(t, n);
}

static void		insert_case2(t_btree *t, t_btree_node *n)
{
	if (node_color(n->parent) == BLACK)
		return ;
	else
		insert_case3(t, n);
}

void			insert_case1(t_btree *t, t_btree_node *n)
{
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(t, n);
}
