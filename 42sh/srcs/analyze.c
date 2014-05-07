/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 13:54:58 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 19:52:54 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

static char		*remove_dquote(char *str)
{
	char		*res;
	int			i;
	int			j;
	int			nb;

	i = 0;
	nb = 0;
	while (str[i++] != '\0')
	{
		if (str[i] == '"')
			nb++;
	}
	if (!(res = (char *)malloc(sizeof(char) * (ft_strlen(str)
								- (size_t)(nb + 1)))))
		print_err("Malloc()", MALLOC);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '"')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

static void		clean(char *end, t_list **list)
{
	int			i;

	i = 0;
	while (get_tk(*list)->text[i])
	{
		if ((quote(get_tk(*list)->text[i])
					|| open_par(get_tk(*list)->text[i]))
				&& get_tk(*list)->text[i] != *end)
		{
			if (*end == '\0')
			{
				*end = get_tk(*list)->text[i];
				if (open_par(*end))
					*end = (*end == '(' ? ')' : *end + 2);
			}
		}
		else if (*end != '\0' && get_tk(*list)->text[i] == *end)
			*end = '\0';
		i++;
	}
}

static int		next(t_list **list, char end)
{
	get_termcap()->shell = SUBSHELL;
	get_termcap()->cmd_subshell = "";
	look_key(get_termcap(), &end);
	if (get_termcap()->shell == SUBSHELL)
	{
		get_termcap()->shell = SHELL;
		get_tk(*list)->text =
			remove_dquote(ft_strjoin(get_tk(*list)->text,
						get_termcap()->cmd_subshell));
		return (1);
	}
	return (0);
}

void			analyze_list(t_list **list)
{
	char		end;
	t_list		*root;

	end = '\0';
	root = *list;
	while (*list)
	{
		clean(&end, list);
		if (end != '\0')
		{
			if (!next(list, end))
			{
				free_list(list);
				*list = lexer(get_termcap()->cmd);
				return (analyze_list(list));
			}
			end = '\0';
		}
		else
			get_tk(*list)->text = remove_dquote(get_tk(*list)->text);
		*list = (*list)->next;
	}
	*list = root;
}
