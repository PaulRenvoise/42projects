/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:09:44 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 17:26:06 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <fcntl.h>
#include <unistd.h>

void		add_or_create_list_start(t_list **list, void *content,
									int content_size)
{
	if (*list == NULL)
		*list = ft_lstnew(content, (size_t)content_size);
	else
		ft_lstadd(list, ft_lstnew(content, (size_t)content_size));
}

void		create_files(t_cmd_tree *root)
{
	int		i;

	if (root)
	{
		create_files(root->left);
		if (root->type == SM_CL)
			return ;
		i = 1;
		while (root->files[i])
		{
			if (ISROUT((root->files[i])->type))
				open((root->files[i])->text, O_CREAT, 0644);
			i++;
		}
		create_files(root->right);
	}
}

void		exec_cmd_or_builtin(t_env *e, t_fd *fd)
{
	if (!check_builtin(e, fd->fd_out))
	{
		if (!check_cmd(e, fd))
			ft_printf_fd("42sh: command not found: %s\n", 2, e->av[0]);
	}
	else
	{
		if (fd->pipe_out)
			fd->fd_in = fd->pipefd[0];
	}
}

void		standard_cmd(t_env *e, t_cmd_tree *root, t_fd *fd)
{
	if (root->type == SIMPLE && root->files[1] == NULL && root->av[0] != NULL)
	{
		e->av = root->av;
		if (fd->pipe_out || fd->pipe_in)
		{
			if (fd->pipe_out)
				fd->fd_out = fd->pipefd[1];
			else
				fd->fd_out = 1;
			if (!fd->pipe_in)
				fd->fd_in = 0;
			exec_cmd_or_builtin(e, fd);
			if (fd->pipe_out)
				close(fd->pipefd[1]);
		}
		else
		{
			exec_cmd_or_builtin(e, fd);
			if (fd->fd_out != 1)
				close(fd->fd_out);
		}
	}
}

t_token		*get_tk(t_list *list)
{
	return ((t_token *)(list->content));
}
