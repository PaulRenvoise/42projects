/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 14:53:01 by prenvois          #+#    #+#             */
/*   Updated: 2014/03/27 19:44:51 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <signal.h>
#include <stdlib.h>
#include <termcap.h>

void		sig_ctrlc(int p)
{
	(void)p;
	if (get_termcap()->cmd)
	{
		free(get_termcap()->cmd);
		get_termcap()->cmd = NULL;
		if (!(get_termcap()->cmd = (char *)malloc(sizeof(char))))
			print_err("Malloc()", MALLOC);
		ft_memset(get_termcap()->cmd, 0, ft_strlen(get_termcap()->cmd));
		get_termcap()->cmd[0] = '\0';
		get_termcap()->cur_char = 0;
		get_termcap()->cur_col = (int)ft_strlen(get_termcap()->prompt);
		get_termcap()->cur_line = 0;
		get_termcap()->tab = 0;
		get_termcap()->start = -1;
		get_termcap()->end = -1;
		if (get_termcap()->list_cmpl)
		{
			free_list_completion(&(get_termcap()->list_cmpl));
			get_termcap()->list_cmpl = NULL;
		}
	}
	ft_putchar_fd('\n', 0);
	get_termcap()->shell = SHELL;
	get_prompt(get_env(), get_termcap());
}

static void	check_child_status(int sig)
{
	if (sig == SIGSEGV)
		ft_putendl_fd("Segmentation fault", 2);
	else if (sig == SIGFPE)
		ft_putendl_fd("Floating-point exception", 2);
	else if (sig == SIGBUS)
		ft_putendl_fd("Bus error", 2);
}

void		sig_child(int p, siginfo_t *t, void *b)
{
	(void)b;
	(void)p;
	if (t->si_code == CLD_STOPPED)
	{
		init_term(get_termcap(), 0);
		ft_putstr("\n42sh: suspended ");
		if (!check_if_in_job_list(get_env()->jobs, t->si_pid))
		{
			ft_putendl(get_termcap()->cmd);
			add_or_create_list_start(&(get_env()->jobs),
			create_job(t->si_pid, get_termcap()->cmd), sizeof(t_job));
		}
		else
			ft_putendl(get_str_job_list(get_env()->jobs, t->si_pid));
	}
	else if (t->si_code == CLD_KILLED || t->si_code == CLD_EXITED)
	{
		init_term(get_termcap(), 0);
		if (t->si_code == CLD_KILLED)
			ft_putchar('\n');
		if (check_if_in_job_list(get_env()->jobs, t->si_pid))
			del_from_job_list(&(get_env()->jobs), t->si_pid, 0);
		check_child_status(t->si_status);
	}
}

void		sig_winch(int sig)
{
	if (sig == SIGWINCH)
	{
		open_session();
		get_termcap()->co = tgetnum("co");
		get_termcap()->cur_line = ((int)(ft_strlen(get_termcap()->cmd)
									+ ft_strlen(get_termcap()->prompt))
									- ((int)ft_strlen(get_termcap()->cmd)
									- get_termcap()->cur_char))
									/ get_termcap()->co;
		if (get_termcap()->cur_line < 1)
			get_termcap()->cur_col = (int)ft_strlen(get_termcap()->prompt)
										+ get_termcap()->cur_char;
		else
			get_termcap()->cur_col = ((int)(ft_strlen(get_termcap()->cmd)
										+ ft_strlen(get_termcap()->prompt))
										% get_termcap()->co)
										- ((int)ft_strlen(get_termcap()->cmd)
										- get_termcap()->cur_char);
	}
}

void		sig_segv(int sig)
{
	(void)sig;
	reset_term(get_termcap(), 1);
}
