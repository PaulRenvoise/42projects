/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 16:01:04 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

t_token			*new_token(char *str, int type)
{
	t_token	*token;

	if (str == NULL)
		return (NULL);
	if (!(token = (t_token *)malloc(sizeof(t_token))))
		print_err("Malloc()", MALLOC);
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->text = ft_strdup(str);
	return (token);
}

int				space_or_tab(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void			add_or_create_list(t_list **list, void *content,
				int content_size)
{
	if (*list == NULL)
		*list = ft_lstnew(content, (size_t)content_size);
	else
		ft_lstadd_end(list, ft_lstnew(content, (size_t)content_size));
}

int				error(char c)
{
	ft_printf_fd("42sh: parse error near `%c'\n", 2, c);
	return (-1);
}
