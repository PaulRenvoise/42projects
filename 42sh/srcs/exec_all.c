/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 17:11:50 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/26 17:12:43 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <signal.h>
#include <termcap.h>
#include <stdlib.h>
#include <unistd.h>

static int				redirections(t_env *e, t_cmd_tree *root, t_fd *fd)
{
	int					i;

	i = 1;
	e->list = NULL;
	while (root->files[i])
	{
		e->av = root->av;
		if (!redirections_out(e, root, fd, &i))
			return (0);
		if (!redirections_in(e, root, fd, &i))
			return (0);
	}
	return (1);
}

static void				assign_pipes(t_cmd_tree *root, t_fd *fd, int call)
{
	if (!call)
	{
		if (root->type == PIPE)
		{
			fd->pipe_out = 0;
			fd->pipe_in = 1;
		}
		else
		{
			fd->pipe_out = 0;
			fd->pipe_in = 0;
		}
	}
	else
	{
		if (root->type == PIPE)
		{
			pipe(fd->pipefd);
			fd->pipe_out = 1;
		}
	}
}

static void				exec_and_or_none(t_cmd_tree *root, t_env *e, t_fd *fd)
{
	if (root->type == AND)
	{
		if (e->ret || (root->right && root->right->type != SIMPLE))
			exec_all(root->right, e, fd);
	}
	else if (root->type == OR)
	{
		if (!e->ret || (root->right && root->right->type != OR
						&& root->right->type != SIMPLE))
			exec_all(root->right, e, fd);
	}
	else
		exec_all(root->right, e, fd);
}

void					exec_all(t_cmd_tree *r, t_env *e, t_fd *fd)
{
	char				*tmp;

	if (r)
	{
		assign_pipes(r, fd, 1);
		create_files(r);
		exec_all(r->left, e, fd);
		if (r->type == SIMPLE && r->av[0] && ft_strchr(r->av[0], '('))
		{
			(r->ac)++;
			if (!(r->av = ft_realloc(r->av, sizeof(char *) * (r->ac + 1))))
				print_err("Realloc()", MALLOC);
			r->av[r->ac] = NULL;
			tmp = ft_strsub(r->av[0], 1, ft_strlen(r->av[0]) - 2);
			r->av[0] = ft_strdup(e->path_bin);
			r->av[1] = ft_strtrim(tmp);
		}
		else if (r->type == SIMPLE && r->av[0])
			backquotes(e, r, fd);
		standard_cmd(e, r, fd);
		if (!redirections(e, r, fd))
			return ;
		assign_pipes(r, fd, 0);
		exec_and_or_none(r, e, fd);
	}
}
