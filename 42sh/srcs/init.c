/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 17:56:32 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 15:50:25 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>
#include <termcap.h>
#include <fcntl.h>

void			init_builtin(t_env *e)
{
	e->builtin[0].f = &builtin_exit;
	e->builtin[0].name = ft_strdup("exit");
	e->builtin[1].f = &builtin_env;
	e->builtin[1].name = ft_strdup("env");
	e->builtin[2].f = &builtin_setenv;
	e->builtin[2].name = ft_strdup("setenv");
	e->builtin[3].f = &builtin_unsetenv;
	e->builtin[3].name = ft_strdup("unsetenv");
	e->builtin[4].f = &builtin_cd;
	e->builtin[4].name = ft_strdup("cd");
	e->builtin[5].f = &builtin_echo;
	e->builtin[5].name = ft_strdup("echo");
	e->builtin[6].f = &builtin_history;
	e->builtin[6].name = ft_strdup("history");
	e->builtin[7].f = &builtin_fg;
	e->builtin[7].name = ft_strdup("fg");
	e->builtin[8].f = &builtin_jobs;
	e->builtin[8].name = ft_strdup("jobs");
}

void			init_env(t_env *e)
{
	int			i;

	i = 0;
	e->paths = NULL;
	e->jobs = NULL;
	while (e->envp[i])
	{
		if (ft_strnstr(e->envp[i], "PATH=", 5) && ((e->envp[i])[4]) == '=')
			e->paths = ft_strsplit(&((e->envp[i])[5]), ':');
		else if (ft_strnstr(e->envp[i], "OLDPWD=", 7)
				&& ((e->envp[i])[6]) == '=')
			e->pwd_old = ft_strdup(&((e->envp[i])[7]));
		else if (ft_strnstr(e->envp[i], "PWD=", 4) && ((e->envp[i])[3]) == '=')
			e->pwd = ft_strdup(&((e->envp[i])[4]));
		else if (ft_strnstr(e->envp[i], "HOME=", 5) && ((e->envp[i])[4]) == '=')
		{
			e->home = ft_strdup(&((e->envp[i])[5]));
			e->home = ft_strjoin("/Volumes/DATA", e->home);
		}
		else if (ft_strnstr(e->envp[i], "USER=", 5) && ((e->envp[i])[4]) == '=')
			e->user = ft_strdup(&((e->envp[i])[5]));
		i++;
	}
}

static void		init_key2(t_termcap *t)
{
	t->keys[12].key = ft_strdup("\033[1;2D");
	t->keys[12].f = &key_shleft;
	t->keys[13].key = ft_strdup("\004");
	t->keys[13].f = &key_ctrld;
	t->keys[14].key = ft_strdup("\011");
	t->keys[14].f = &key_tab;
	t->keys[15].key = ft_strdup("226.137.136");
	t->keys[15].f = &key_altx;
	t->keys[16].key = ft_strdup("195.167.0");
	t->keys[16].f = &key_altc;
	t->keys[17].key = ft_strdup("226.136.154");
	t->keys[17].f = &key_altv;
	t->keys[18].key = ft_strdup("\033[1;9D");
	t->keys[18].f = &key_altleft;
	t->keys[19].key = ft_strdup("\033[1;9C");
	t->keys[19].f = &key_altright;
	t->keys[20].key = ft_strdup("\033\033[D");
	t->keys[20].f = &key_altleft;
	t->keys[21].key = ft_strdup("\033\033[C");
	t->keys[21].f = &key_altright;
}

void			init_key(t_termcap *t)
{
	t->keys[0].key = ft_strdup("\033[D");
	t->keys[0].f = &key_left;
	t->keys[1].key = ft_strdup("\033[C");
	t->keys[1].f = &key_right;
	t->keys[2].key = ft_strdup("\033[B");
	t->keys[2].f = &key_down;
	t->keys[3].key = ft_strdup("\033[A");
	t->keys[3].f = &key_up;
	t->keys[4].key = ft_strdup("\n");
	t->keys[4].f = &key_ret;
	t->keys[5].key = ft_strdup("\177");
	t->keys[5].f = &key_delete;
	t->keys[6].key = ft_strdup("\033[3~");
	t->keys[6].f = &key_del;
	t->keys[7].key = ft_strdup("\033[H");
	t->keys[7].f = &key_home;
	t->keys[8].key = ft_strdup("\033[F");
	t->keys[8].f = &key_end;
	t->keys[9].key = ft_strdup("\033[1;2A");
	t->keys[9].f = &key_shup;
	t->keys[10].key = ft_strdup("\033[1;2B");
	t->keys[10].f = &key_shdown;
	t->keys[11].key = ft_strdup("\033[1;2C");
	t->keys[11].f = &key_shright;
	init_key2(t);
}

void			init_fd(t_fd *fd, char *file)
{
	fd->pipe_in = 0;
	fd->pipe_out = 0;
	fd->fd_in = 0;
	fd->fd_out = 1;
	if (file != NULL)
		fd->fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (fd->fd_out == -1)
		fd->fd_out = 1;
}
