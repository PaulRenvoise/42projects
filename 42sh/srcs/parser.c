/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:27:26 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:32:19 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>
#include <unistd.h>

t_cmd_tree		*command(t_list **list)
{
	t_cmd_tree	*cmd;
	t_cmd_tree	*tmp;

	tmp = NULL;
	cmd = and_or(list);
	while (*list && (get_tk(*list)->type == SM_CL))
	{
		if (!cmd)
		{
			ft_putendl_fd("42sh: parse error: null command", 2);
			free_tree(&cmd);
			return (NULL);
		}
		tmp = cmd;
		cmd = new_cmd_tree();
		cmd->type = get_tk(*list)->type;
		cmd->left = tmp;
		*list = (*list)->next;
		cmd->right = command(list);
	}
	return (cmd);
}

t_cmd_tree		*and_or(t_list **list)
{
	t_cmd_tree	*cmd;
	t_cmd_tree	*tmp;

	cmd = pipe_line(list);
	while (*list && (get_tk(*list)->type == AND || get_tk(*list)->type == OR))
	{
		if (!cmd)
		{
			ft_putendl_fd("42sh: parse error: null command", 2);
			return (NULL);
		}
		tmp = cmd;
		cmd = new_cmd_tree();
		cmd->type = get_tk(*list)->type;
		cmd->left = tmp;
		*list = (*list)->next;
		cmd->right = and_or(list);
		if (!cmd->right)
		{
			ft_putendl_fd("42sh: parse error: null command", 2);
			free_tree(&cmd);
			return (NULL);
		}
	}
	return (cmd);
}

t_cmd_tree		*pipe_line(t_list **list)
{
	t_cmd_tree	*cmd;
	t_cmd_tree	*tmp;

	cmd = stage(list);
	while (*list && (get_tk(*list)->type == PIPE))
	{
		if (!cmd)
		{
			ft_putendl_fd("42sh: parse error: null command", 2);
			return (NULL);
		}
		tmp = cmd;
		cmd = new_cmd_tree();
		cmd->type = get_tk(*list)->type;
		cmd->left = tmp;
		*list = (*list)->next;
		cmd->right = pipe_line(list);
		if (!cmd->right)
		{
			ft_putendl_fd("42sh: parse error: null command", 2);
			free_tree(&cmd);
			return (NULL);
		}
	}
	return (cmd);
}

t_cmd_tree		*stage(t_list **list)
{
	t_cmd_tree	*cmd;
	t_cmd_tree	*tmp;

	tmp = NULL;
	cmd = NULL;
	if (!*list)
		return (NULL);
	tmp = new_cmd_tree();
	while (*list && (ISRIN(get_tk(*list)->type) || ISROUT(get_tk(*list)->type)))
	{
		if (!(tmp = redirect(tmp, list, 0)))
			return (NULL);
	}
	if (!*list)
	{
		ft_putendl_fd("42sh: parse error: null command", 2);
		free_tree(&cmd);
		return (NULL);
	}
	else
		cmd = simple(list);
	cmd = merge(cmd, tmp, 1, 1);
	free_tree(&tmp);
	return (cmd);
}

t_cmd_tree		*simple(t_list **list)
{
	t_cmd_tree	*cmd;

	cmd = new_cmd_tree();
	cmd->type = SIMPLE;
	while (*list && cmd != NULL)
	{
		if (get_tk(*list)->type == SIMPLE)
		{
			(cmd->ac)++;
			if (!(cmd->av = ft_realloc(cmd->av, sizeof(char *)
										* (size_t)(cmd->ac + 1))))
				print_err("Realloc()", MALLOC);
			cmd->av[cmd->ac] = NULL;
			cmd->av[cmd->ac - 1] = ft_strdup(get_tk(*list)->text);
			*list = (*list)->next;
		}
		else if (ISRIN(get_tk(*list)->type) || ISROUT(get_tk(*list)->type))
			cmd = redirect(cmd, list, 0);
		else
			break ;
	}
	if (!cmd || !cmd->av)
		return (NULL);
	else
		return (cmd);
}
