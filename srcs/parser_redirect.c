/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 17:59:02 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:29:37 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>
#include <unistd.h>

static int		heredoc(t_cmd_tree *cmd, t_list **list)
{
	pipe(cmd->heredoc);
	get_termcap()->heredoc_fd = (cmd->heredoc)[1];
	get_termcap()->shell = HERESHELL;
	*list = (*list)->next;
	look_key(get_termcap(), get_tk(*list)->text);
	if (get_termcap()->shell == SHELL)
	{
		free_tree(&cmd);
		*list = lexer(get_termcap()->cmd);
		analyze_list(list);
		return (1);
	}
	else
		get_termcap()->shell = SHELL;
	close(cmd->heredoc[1]);
	return (0);
}

static int		error_redirection(t_cmd_tree *cmd, t_list **list, int i)
{
	*list = (*list)->next;
	if (!*list || get_tk(*list)->type != SIMPLE)
	{
		ft_putendl_fd("42sh: parse error: missing file name", 2);
		free_tree(&cmd);
		return (1);
	}
	(cmd->files[i])->text = ft_strdup(get_tk(*list)->text);
	return (0);
}

t_cmd_tree		*redirect(t_cmd_tree *cmd, t_list **list, int i)
{
	if (ISRIN(get_tk(*list)->type) || ISROUT(get_tk(*list)->type))
	{
		while (cmd->files[i])
			i++;
		if (!(cmd->files = (t_token**)ft_realloc(cmd->files, sizeof(t_token)
													* (size_t)(i + 2))))
			print_err("Realloc()", MALLOC);
		if (!(cmd->files[i] = (t_token *)malloc(sizeof(t_token))))
			print_err("Malloc()", MALLOC);
		cmd->files[i + 1] = NULL;
		(cmd->files[i])->type = get_tk(*list)->type;
		if (get_tk(*list)->type == RED_IN_HER)
		{
			if (heredoc(cmd, list))
				return (parse(list));
		}
		else
		{
			if (error_redirection(cmd, list, i))
				return (NULL);
		}
	}
	*list = (*list)->next;
	return (cmd);
}
