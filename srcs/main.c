/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:27:13 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 19:51:43 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <signal.h>
#include <termcap.h>
#include <stdlib.h>
#include <unistd.h>

static void				check_param(t_termcap *t, char *param, char **cmd,
									int call)
{
	if (call)
	{
		if (!param)
		{
			get_termcap()->shell = SHELL;
			*cmd = look_key(t, 0);
		}
		else
			*cmd = ft_strdup(param);
	}
	else
	{
		if (param)
		{
			reset_term(t, 0);
			exit(0);
		}
		signal(SIGINT, &sig_ctrlc);
	}
}

static void				start_prompt(t_env *e, t_termcap *t, char *param,
									char *file)
{
	char		*cmd;
	t_cmd_tree	*root;
	t_list		*list;
	t_fd		fd;

	if (!param)
		get_prompt(e, t);
	while (42)
	{
		check_param(t, param, &cmd, 1);
		if ((cmd && ft_strcmp("", cmd) != 0 && notonlyspace(cmd)))
		{
			list = lexer(cmd);
			analyze_list(&list);
			root = parse(&list);
			init_fd(&fd, file);
			exec_all(root, e, &fd);
			free_list(&list);
			free_tree(&root);
		}
		check_param(t, param, &cmd, 0);
		get_prompt(e, t);
	}
}

static void				check_signals(void)
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	sig.sa_mask = SA_NODEFER;
	sig.sa_sigaction = sig_child;
	sigaction(SIGCHLD, &sig, NULL);
	signal(SIGINT, &sig_ctrlc);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSEGV, &sig_segv);
	signal(SIGWINCH, &sig_winch);
}

static void				init_sh(char **argv)
{
	init_env(get_env());
	create_trees_cmd(get_termcap(), get_env());
	open_session();
	init_term(get_termcap(), 1);
	check_signals();
	init_builtin(get_env());
	init_key(get_termcap());
	start_prompt(get_env(), get_termcap(), argv[1], argv[2]);
}

int						main(int argc, char **argv, char **envp)
{
	if (argc == 2)
	{
		if (ft_strcmp(argv[1], "--help") == 0)
		{
			display_help();
			return (0);
		}
	}
	else if (argc == 1)
		display_name();
	get_env()->envp = envp;
	get_env()->path_bin = argv[0];
	get_termcap()->history = NULL;
	get_termcap()->head = NULL;
	get_termcap()->cmd = NULL;
	if (!(get_termcap()->completion = (t_btree *)malloc(sizeof(t_btree))))
		print_err("Malloc()", MALLOC);
	get_termcap()->completion = NULL;
	get_termcap()->list_cmpl = NULL;
	get_termcap()->clipboard = NULL;
	init_sh(argv);
	return (0);
}
