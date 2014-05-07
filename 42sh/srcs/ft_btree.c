/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 15:52:37 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

void				add_or_create_dllist(t_dllist **list, void *content,
					int content_size)
{
	if (*list == NULL)
		*list = ft_dllstnew(content, (size_t)content_size);
	else
		ft_dllstadd_end(list, ft_dllstnew(content, (size_t)content_size));
}

void				ft_btree_search_node(t_dllist **list, t_btree_node *t,
					char *data_ref,
					int (*cmpf)(const char *, const char *, size_t n))
{
	int				comp_result;

	if (t != NULL)
	{
		ft_btree_search_node(list, t->left, data_ref, cmpf);
		comp_result = cmpf(data_ref, (t->item)->name, ft_strlen(data_ref));
		if (comp_result == 0)
		{
			add_or_create_dllist(list, (t->item)->name,
					(int)ft_strlen((t->item)->name) + 1);
		}
		ft_btree_search_node(list, t->right, data_ref, cmpf);
	}
}

t_btree_node		*ft_btree_create_node(t_item *item, t_color color,
					t_btree_node *left, t_btree_node *right)
{
	t_btree_node	*node;

	if (!(node = (t_btree_node *)malloc(sizeof(t_btree_node))))
		print_err("Malloc()", MALLOC);
	node->color = color;
	node->item = item;
	node->right = right;
	node->left = left;
	if (left != NULL)
		left->parent = node;
	if (right != NULL)
		right->parent = node;
	node->parent = NULL;
	return (node);
}

t_btree				*ft_btree_create(void)
{
	t_btree			*t;

	if (!(t = (t_btree *)malloc(sizeof(t_btree))))
		print_err("Malloc()", MALLOC);
	t->root = NULL;
	return (t);
}
