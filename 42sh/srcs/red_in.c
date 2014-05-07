/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 17:57:36 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/25 19:14:20 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <fcntl.h>
#include <unistd.h>

static void	redirections_in_out(t_env *e, t_cmd_tree *root, t_fd *fd, int *j)
{
	if (ISROUT((root->files[*j])->type))
	{
		if ((root->files[*j])->type == RED_OUT_TRUNC)
			fd->fd_out = open((root->files[*j])->text, O_WRONLY | O_TRUNC);
		else
			fd->fd_out = open((root->files[*j])->text, O_WRONLY | O_APPEND);
		exec_cmd_or_builtin(e, fd);
		if (fd->fd_out != 1)
			close(fd->fd_out);
		add_or_create_list(&(e->list),
				new_token((root->files[*j]->text),
					(root->files[*j])->type), sizeof(t_token));
		if (fd->pipe_out)
		{
			fd->fd_out = fd->pipefd[1];
			fd->fd_in = open((root->files[*j])->text, O_RDONLY);
			exec_cmd_or_builtin(e, fd);
		}
	}
	(*j)++;
}

static int	init_red_in(t_cmd_tree *root, int i, t_fd *fd)
{
	if ((root->files[i])->type == RED_IN)
		fd->fd_in = open((root->files[i])->text, O_RDONLY);
	else
		fd->fd_in = root->heredoc[0];
	if (fd->fd_in == -1)
	{
		ft_printf_fd("42sh: no such file or directory: %s\n", 2,
					(root->files[i])->text);
		return (0);
	}
	return (1);
}

static void	exec_simple_red_in(t_env *e, t_fd *fd)
{
	if (fd->pipe_out)
	{
		fd->fd_out = fd->pipefd[1];
		exec_cmd_or_builtin(e, fd);
		close(fd->pipefd[1]);
	}
	else
	{
		exec_cmd_or_builtin(e, fd);
		if (fd->fd_out != 1)
			close(fd->fd_out);
	}
}

int			redirections_in(t_env *e, t_cmd_tree *root, t_fd *fd, int *i)
{
	int		j;

	while (root->files[*i] != NULL && ISRIN((root->files[*i])->type))
	{
		if (!seek_in_list(e->list, root->files[*i]))
		{
			if (!init_red_in(root, *i, fd))
				return (0);
			if (root->files[*i + 1] != NULL)
			{
				j = *i + 1;
				while (root->files[j] != NULL)
					redirections_in_out(e, root, fd, &j);
			}
			else
				exec_simple_red_in(e, fd);
			if (fd->fd_in != 0 && !fd->pipe_out)
				close(fd->fd_in);
			if (fd->pipe_out && root->files[*i + 1] != NULL
					&& (root->files[*i + 1])->type != RED_IN)
				close(fd->pipefd[1]);
		}
		(*i)++;
	}
	return (1);
}
