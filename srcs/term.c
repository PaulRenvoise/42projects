/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 12:29:05 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/26 15:36:15 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>

void			write_list_reset(t_termcap *t, char *file)
{
	int			fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (fd != -1)
	{
		if (t->history)
		{
			while (t->history->next)
				t->history = t->history->next;
			while (t->history)
			{
				ft_putendl_fd(t->history->content, fd);
				t->history = t->history->prev;
			}
		}
		close(fd);
	}
}

int				reset_term(t_termcap *t, int write_list)
{
	char		*name;

	if (write_list)
	{
		name = ft_strdup("/.42sh_hist");
		name = ft_strjoin(get_env()->home, name);
		write_list_reset(t, name);
		while (get_env()->jobs)
		{
			kill(((t_job *)(get_env()->jobs->content))->pid, SIGKILL);
			get_env()->jobs = get_env()->jobs->next;
		}
	}
	tputs(tgetstr("ei", NULL), 1, ft_output);
	if (tcsetattr(1, TCSANOW, get_termios()) < 0)
		return (-1);
	return (0);
}

void			open_session(void)
{
	char		*xterm;

	if ((xterm = getenv("TERM")) == NULL)
		print_err(NULL, TERM);
	if (tgetent(0, xterm) != 1)
		print_err(NULL, GETENT);
}

int				write_list_init(t_termcap *t, char *file, int flag_fd)
{
	char		*line;
	int			fd;
	int			ret;

	if (!(line = NULL) && t->history)
	{
		free_list_completion(&t->history);
		t->history = NULL;
		t->head = NULL;
	}
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		open(file, O_CREAT, 0744);
		return (0);
	}
	while ((ret = get_next_line(fd, &line, flag_fd)) && ret != -1)
	{
		if (flag_fd == 0)
			flag_fd = 1;
		add_or_create_list_history(t, line);
		free(line);
	}
	t->head = t->history;
	close(fd);
	return (1);
}

int				init_term(t_termcap *t, int write_list)
{
	char		*name;

	if (tcgetattr(1, get_termios()) < 0)
		return (-1);
	*get_newterm() = *get_termios();
	get_newterm()->c_lflag &= (unsigned long)~(ECHO | ICANON);
	get_newterm()->c_cc[VMIN] = 1;
	get_newterm()->c_cc[VTIME] = 0;
	tcsetattr(1, TCSANOW, get_newterm());
	tputs(tgetstr("im", NULL), 1, ft_output);
	if (get_env()->home && write_list)
	{
		name = ft_strdup("/.42sh_hist");
		name = ft_strjoin(get_env()->home, name);
		if (write_list_init(t, name, 0) == 0)
			return (0);
	}
	return (0);
}
