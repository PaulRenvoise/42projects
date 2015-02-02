/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:26:26 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 17:11:44 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>

static void		assign_fds(t_fd *fd, int call)
{
	if (call)
	{
		if (fd->fd_in != 0)
			dup2(fd->fd_in, 0);
		if (fd->fd_out != 1)
			dup2(fd->fd_out, 1);
	}
	else
	{
		if (fd->pipe_in && !fd->pipe_out)
			close(fd->pipefd[0]);
		if (fd->pipe_out)
			fd->fd_in = fd->pipefd[0];
	}
}

void			execute_cmd(char *cmd, t_env *e, t_fd *fd)
{
	pid_t		pid;
	int			ret;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid < 0)
		exit(0);
	else if (pid == 0)
	{
		reset_term(get_termcap(), 0);
		assign_fds(fd, 1);
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		execve(cmd, e->av, e->envp);
	}
	else
	{
		waitpid(pid, &ret, WUNTRACED);
		e->ret = 1;
		if (WEXITSTATUS(ret))
			e->ret = 0;
		assign_fds(fd, 0);
	}
}
