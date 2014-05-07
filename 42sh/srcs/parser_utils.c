/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 16:30:08 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 14:32:01 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <stdlib.h>

static void		free_token(t_token **token)
{
	int			i;

	i = 1;
	while (token[i])
	{
		free((token[i])->text);
		i++;
	}
}

t_cmd_tree		*new_cmd_tree(void)
{
	t_cmd_tree	*new;

	if (!(new = (t_cmd_tree *)malloc(sizeof(t_cmd_tree))))
		print_err("Malloc()", MALLOC);
	new->ac = 0;
	if (!(new->av = (char **)malloc(sizeof(char *))))
		print_err("Malloc()", MALLOC);
	new->av[0] = NULL;
	if (!(new->files = (t_token **)malloc(sizeof(t_token*) * 2)))
		print_err("Malloc()", MALLOC);
	new->files[1] = NULL;
	if (!(new->files[0] = (t_token *)malloc(sizeof(t_token))))
		print_err("Malloc()", MALLOC);
	(new->files[0])->type = NONE;
	(new->files[0])->text = "none";
	new->left = NULL;
	new->right = NULL;
	new->type = NONE;
	return (new);
}

static void		copy(t_cmd_tree *cmd, t_cmd_tree *cmd2, int *i)
{
	if (!(cmd->files = (t_token**)ft_realloc(cmd->files, sizeof(t_token)
											* (size_t)(*i + 2))))
		print_err("Realloc()", MALLOC);
	if (!(cmd->files[*i] = (t_token *)malloc(sizeof(t_token))))
		print_err("Malloc()", MALLOC);
	(cmd->files[*i])->type = (cmd2->files[*i])->type;
	(cmd->files[*i])->text = ft_strdup((cmd2->files[*i])->text);
	(*i)++;
}

t_cmd_tree		*merge(t_cmd_tree *cmd, t_cmd_tree *cmd2, int i, int j)
{
	t_token		**tmp;

	if (!cmd || !cmd2)
		return (NULL);
	tmp = cmd->files;
	while (cmd2->files[i])
		copy(cmd, cmd2, &i);
	while (tmp[j])
	{
		if (!(cmd->files = (t_token**)ft_realloc(cmd->files, sizeof(t_token)
												* (size_t)(i + 2))))
			print_err("Realloc()", MALLOC);
		if (!(cmd->files[i] = (t_token *)malloc(sizeof(t_token))))
			print_err("Malloc()", MALLOC);
		(cmd->files[i])->type = (tmp[j])->type;
		(cmd->files[i])->text = ft_strdup((tmp[j])->text);
		i++;
		j++;
	}
	if (cmd2->files[1] != NULL)
		cmd->files[i] = NULL;
	free_token(tmp);
	return (cmd);
}

t_cmd_tree		*parse(t_list **list)
{
	t_cmd_tree	*root;

	root = command(list);
	if (root && *list != NULL)
	{
		ft_putendl_fd("parse error: too many commands", 2);
		free_tree(&root);
		return (NULL);
	}
	return (root);
}
