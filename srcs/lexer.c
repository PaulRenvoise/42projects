/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:26:48 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sh42.h>

static int			define_type(char *str)
{
	int				type;

	if (ft_strcmp(">>", str) == 0)
		type = RED_OUT_APP;
	else if (ft_strcmp(">", str) == 0)
		type = RED_OUT_TRUNC;
	else if (ft_strcmp("<", str) == 0)
		type = RED_IN;
	else if (ft_strcmp("<<", str) == 0)
		type = RED_IN_HER;
	else if (ft_strcmp("|", str) == 0)
		type = PIPE;
	else if (ft_strcmp(";", str) == 0)
		type = SM_CL;
	else if (ft_strcmp("&&", str) == 0)
		type = AND;
	else if (ft_strcmp("||", str) == 0)
		type = OR;
	else if (!split(str[0]) && !space_or_tab(str[0]))
		type = SIMPLE;
	else
		return (error(str[0]));
	return (type);
}

static int			parenthesis(char *s, int *j)
{
	char			c;

	if (close_par(s[*j]))
		return (error(s[*j]));
	if (open_par(s[*j]))
	{
		c = (s[*j] == '(' ? ')' : s[*j] + 2);
		(*j)++;
		while (s[*j] != '\0' && s[*j] != c)
			(*j)++;
		(*j)++;
		return (0);
	}
	return (1);
}

static int			move_forward(char *s, int *j)
{
	char			c;

	if (parenthesis(s, j) == 1)
	{
		if (quote(s[*j]))
		{
			c = s[*j];
			(*j)++;
			while (s[*j] != '\0' && s[*j] != c)
				(*j)++;
			(*j)++;
			return (1);
		}
		else if (!split(s[*j]) && !space_or_tab(s[*j]))
			while (!split(s[*j]) && !space_or_tab(s[*j]) && s[*j] != '\0')
				(*j)++;
		else if (split(s[*j]))
		{
			c = s[*j];
			while (split(s[*j]) && !space_or_tab(s[*j])
					&& s[*j] != '\0' && s[*j] == c)
				(*j)++;
		}
	}
	return (0);
}

static int			add_in_list(t_list **list, char *tmp, int i, int j)
{
	int				type;

	if (tmp[0] == '~')
		tmp = ft_strjoin(get_env()->home, tmp + 1);
	if ((type = define_type(tmp)) == -1 || j == i)
		return (0);
	add_or_create_list(list, new_token(tmp, type), sizeof(t_token));
	return (1);
}

t_list				*lexer(char *s)
{
	t_list			*list;
	int				i;
	int				j;
	char			*tmp;
	int				ret;

	list = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		while (space_or_tab(s[i]) && s[i] != '\0')
			i++;
		j = i;
		if ((ret = move_forward(s, &j)) == -1)
			return (NULL);
		tmp = ft_strsub(s, (unsigned int)i, (size_t)(j - i));
		if (!add_in_list(&list, tmp, i, j))
			return (NULL);
		while (space_or_tab(s[j]) && s[j] != '\0')
			j++;
		i = j;
	}
	return (list);
}
