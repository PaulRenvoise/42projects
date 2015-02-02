/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmergesort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 16:18:22 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/11 16:45:03 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*ft_lstsorted(t_list *split1, t_list *split2)
{
	t_list		*ret;

	ret = NULL;
	if (!split1)
		return (split2);
	else if (!split2)
		return (split1);
	if (ft_strcmp(split1->content, split2->content) < 0
		|| !ft_strcmp(split1->content, split2->content))
	{
		ret = split1;
		ret->next = ft_lstsorted(split1->next, split2);
	}
	else
	{
		ret = split2;
		ret->next = ft_lstsorted(split1, split2->next);
	}
	return (ret);
}

static void		ft_lstsplit(t_list *root, t_list **split1, t_list **split2)
{
	t_list		*slow;
	t_list		*fast;

	if (!root || !root->next)
	{
		(*split1) = root;
		split2 = NULL;
	}
	else
	{
		slow = root;
		fast = root->next;
		while (fast)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		(*split1) = root;
		(*split2) = slow->next;
		slow->next = NULL;
	}
}

void			ft_lstmergesort(t_list **alst)
{
	t_list		*tmp;
	t_list		*split1;
	t_list		*split2;

	tmp = (*alst);
	if (!(*alst) || !(*alst)->next)
		return ;
	ft_lstsplit(tmp, &split1, &split2);
	ft_lstmergesort(&split1);
	ft_lstmergesort(&split2);
	(*alst) = ft_lstsorted(split1, split2);
}
