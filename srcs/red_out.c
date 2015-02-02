/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:03:42 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 16:04:48 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sh42.h>

static void	exec_simple_red_out(t_env *e, t_fd *fd)
{
	exec_cmd_or_builtin(e, fd);
	if (fd->pipe_out)
	{
		fd->fd_out = fd->pipefd[1];
		exec_cmd_or_builtin(e, fd);
		close(fd->pipefd[1]);
	}
	else
	{
		if (fd->fd_in != 0)
			close(fd->fd_in);
	}
}

static int	redirections_out_in(t_env *e, t_cmd_tree *r, t_fd *fd, int *j)
{
	t_token	*t;

	if (ISRIN((r->files[*j])->type))
	{
		fd->fd_out = fd->tmp_out;
		fd->fd_in = open((r->files[*j])->text, O_RDONLY);
		if (fd->fd_in == -1)
		{
			ft_printf_fd("42sh: no such file: %s\n", 2, (r->files[*j])->text);
			return (0);
		}
		exec_cmd_or_builtin(e, fd);
		if (fd->fd_in != 0)
			close(fd->fd_in);
		t = new_token(r->files[*j]->text, r->files[*j]->type);
		add_or_create_list(&(e->list), t, sizeof(t_token));
		if (fd->pipe_out)
		{
			fd->fd_in = open((r->files[*j])->text, O_RDONLY);
			fd->fd_out = fd->pipefd[1];
			exec_cmd_or_builtin(e, fd);
		}
	}
	(*j)++;
	return (1);
}

static int	init_red_out(t_token *elem, t_fd *fd)
{
	if (elem->type == RED_OUT_TRUNC)
		fd->fd_out = open(elem->text, O_WRONLY | O_TRUNC);
	else
		fd->fd_out = open(elem->text, O_WRONLY | O_APPEND);
	if (fd->fd_out == -1)
	{
		ft_printf_fd("42sh: permission denied: %s\n", 2, elem->text);
		return (0);
	}
	fd->tmp_out = fd->fd_out;
	return (1);
}

int			redirections_out(t_env *e, t_cmd_tree *root, t_fd *fd, int *i)
{
	int		j;

	while (root->files[*i] != NULL && ISROUT((root->files[*i])->type))
	{
		if (!seek_in_list(e->list, root->files[*i]))
		{
			if (!init_red_out(root->files[*i], fd))
				return (0);
			if (root->files[*i + 1] != NULL)
			{
				j = *i + 1;
				while (root->files[j] != NULL)
				{
					if (!redirections_out_in(e, root, fd, &j))
						return (0);
				}
			}
			else
				exec_simple_red_out(e, fd);
			if (fd->fd_out != 1)
				close(fd->fd_out);
		}
		(*i)++;
	}
	return (1);
}
