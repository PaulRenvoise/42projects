/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbrieuc <rbrieuc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 16:27:18 by rbrieuc           #+#    #+#             */
/*   Updated: 2014/03/27 15:33:35 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# define SHELL 0
# define SUBSHELL 1
# define HERESHELL 2
# define NB_READ_KEY 7
# define NB_KEYS 22
# define NB_BUILT_IN 9
# define ISRIN(x) ((x) == RED_IN || (x) == RED_IN_HER)
# define ISROUT(x) ((x) == RED_OUT_TRUNC || (x) == RED_OUT_APP)
# define ABS(x) ((x) < 0 ? - (x) : (x))

# include <libft.h>
# include <signal.h>
# include <dirent.h>

typedef struct dirent		t_dirent;

enum						e_type
{
	RED_OUT_APP,
	RED_OUT_TRUNC,
	RED_IN,
	RED_IN_HER,
	PIPE,
	SM_CL,
	AND,
	OR,
	SIMPLE,
	ERROR,
	SUB_SHELL,
	NONE
};

enum						e_errcode
{
	MALLOC = 40,
	TERM,
	GETENT
};

typedef struct				s_fd
{
	int						pipefd[2];
	int						fd_in;
	int						fd_out;
	int						pipe_in;
	int						pipe_out;
	int						tmp_out;
}							t_fd;

typedef struct s_env		t_env;

typedef struct				s_builtin
{
	char					*name;
	int						(*f)(t_env *e, int fd);
}							t_builtin;

struct						s_env
{
	char					**paths;
	char					*pwd;
	char					*pwd_old;
	char					**av;
	char					**envp;
	char					*home;
	char					*user;
	char					*path_bin;
	t_list					*jobs;
	int						ac;
	int						ret;
	t_list					*list;
	t_builtin				builtin[NB_BUILT_IN];
};

typedef struct				s_item
{
	char					*name;
	char					*value;
}							t_item;

typedef enum				e_color
{
	RED,
	BLACK
}							t_color;

typedef struct				s_job
{
	int						pid;
	char					*str;
}							t_job;

typedef struct				s_btree_node
{
	struct s_btree_node		*right;
	struct s_btree_node		*left;
	struct s_btree_node		*parent;
	t_item					*item;
	t_color					color;
}							t_btree_node;

typedef struct				s_btree
{
	t_btree_node			*root;
}							t_btree;

typedef struct s_termcap	t_termcap;

typedef struct				s_key
{
	char					*key;
	int						(*f)(t_termcap *);
}							t_key;

struct						s_termcap
{
	t_key					keys[NB_KEYS];
	char					*cmd;
	char					*cmd_save;
	int						cur_col;
	int						cur_char;
	int						cur_line;
	int						tab;
	char					*prompt;
	int						start;
	int						end;
	int						shell;
	int						co;
	char					*clipboard;
	char					*cmd_subshell;
	int						heredoc_fd;
	t_dllist				*history;
	t_dllist				*head;
	t_dllist				*list_cmpl;
	t_dllist				*head_completion;
	t_btree					*completion;
};

typedef struct				s_token
{
	char					*text;
	int						type;
}							t_token;

typedef struct				s_cmd_tree
{
	int						ac;
	char					**av;
	t_token					**files;
	int						type;
	int						heredoc[2];
	struct s_cmd_tree		*left;
	struct s_cmd_tree		*right;
}							t_cmd_tree;

/*
** analyze.c
*/

void						analyze_list(t_list **list);

/*
** auto_completion.c
*/

int							key_tab(t_termcap *t);

/*
** backquotes.c
*/
void						backquotes(t_env *e, t_cmd_tree *root, t_fd *fd);

/*
** builtin_cd.c
*/

int							builtin_cd(t_env *e, int fd);

/*
** builtin_echo.c
*/

int							builtin_echo(t_env *e, int fd);

/*
** builtin_env.c
*/

int							builtin_env(t_env *e, int fd);

/*
** builtin_exit.c
*/

int							builtin_exit(t_env *e, int fd);

/*
** builtin_fg.c
*/

int							builtin_fg(t_env *e, int fd);

/*
** builtin_history.c
*/

int							builtin_history(t_env *e, int fd);

/*
** builtin_history_options.c
*/

void						option_c(void);
void						option_d(int n);
void						option_a(char *file);
void						option_r(char *file);

/*
** builtin_jobs.c
*/

t_job						*create_job(int pid, char *str);

/*
** builtin_jobs_utils.c
*/

int							check_if_in_job_list(t_list *list, int pid);
char						*get_str_job_list(t_list *list, int pid);
void						del_from_job_list(t_list **list, int pid, int i);
int							builtin_jobs(t_env *e, int fd);

/*
** builtin_setenv.c
*/

int							builtin_setenv(t_env *e, int fd);

/*
** builtin_unsetenv.c
*/

int							builtin_unsetenv(t_env *e, int fd);

/*
** check_builtin_or_cmd.c
*/

int							check_cmd(t_env *e, t_fd *fd);
int							check_builtin(t_env *e, int fd);

/*
** errors.c
*/

void						print_err(char *info, int errcode);

/*
** exec_all.c
*/

void						exec_all(t_cmd_tree *r, t_env *e, t_fd *fd);

/*
** execute_cmd.c
*/

void						execute_cmd(char *cmd, t_env *e, t_fd *fd);

/*
** free.c
*/

void						free_tree(t_cmd_tree **root);
void						free_list(t_list **list);
void						free_list_completion(t_dllist **list);
void						free_all(t_termcap *t, t_env *e);

/*
** ft_btree.c
*/

void						ft_btree_search_node(t_dllist **list,
							t_btree_node *t, char *data_ref,
							int (*cmpf)(const char *, const char *, size_t n));
void						add_or_create_dllist(t_dllist **list, void *content,
							int content_size);
t_btree_node				*ft_btree_create_node(t_item *item, t_color color,
							t_btree_node *left, t_btree_node *right);
t_btree						*ft_btree_create(void);

/*
** ft_btree_insert_node.c
*/

void						ft_btree_insert_node(t_btree *t, t_item *item,
							int (*cmpf)(const char *, const char *));
void						rotate_left(t_btree *t, t_btree_node *n);
void						rotate_right(t_btree *t, t_btree_node *n);

/*
** ft_btree_insert_node_case.c
*/

void						insert_case1(t_btree *t, t_btree_node *n);

/*
** ft_btree_insert_node_utils.c
*/

t_btree_node				*sibling(t_btree_node *n);
t_btree_node				*uncle(t_btree_node *n);
t_btree_node				*grandparent(t_btree_node *n);
t_color						node_color(t_btree_node *n);
void						replace_node(t_btree *t, t_btree_node *oldn,
							t_btree_node *newn);

/*
** init.c
*/

void						init_fd(t_fd *fd, char *file);
void						init_key(t_termcap *t);
void						init_env(t_env *e);
void						init_builtin(t_env *e);

/*
** lexer.c
*/

t_list						*lexer(char *s);

/*
** lexer_utils.c
*/

t_token						*new_token(char *str, int type);
int							space_or_tab(char c);
void						add_or_create_list(t_list **list, void *content,
							int content_size);
int							error(char c);

/*
** list_completion.c
*/

void						create_list_completion(t_termcap *t, char *search);

/*
** main.c
*/

int							main(int argc, char **argv, char **envp);

/*
** misc.c
*/

void						display_name(void);
void						display_help(void);
void						get_prompt(t_env *e, t_termcap *t);

/*
** parser.c
*/

t_cmd_tree					*command(t_list **list);
t_cmd_tree					*and_or(t_list **list);
t_cmd_tree					*pipe_line(t_list **list);
t_cmd_tree					*stage(t_list **list);
t_cmd_tree					*simple(t_list **list);

/*
** parser_redirect.c
*/

t_cmd_tree					*redirect(t_cmd_tree *cmd, t_list **list, int i);

/*
** parser_utils.c
*/

t_cmd_tree					*new_cmd_tree(void);
t_cmd_tree					*merge(t_cmd_tree *cmd, t_cmd_tree *cmd2, int i,
							int j);
t_cmd_tree					*parse(t_list **list);

/*
** red_in.c
*/

int							redirections_in(t_env *e, t_cmd_tree *root,
							t_fd *fd, int *i);

/*
** red_out.c
*/

int							redirections_out(t_env *e, t_cmd_tree *root,
							t_fd *fd, int *i);

/*
** seek.c
*/

int							seek_pipe(t_cmd_tree *root);
int							seek_in_list(t_list *list, t_token *tk);

/*
** signals.c
*/

void						sig_ctrlc(int p);
void						sig_child(int p, siginfo_t *t, void *b);
void						sig_winch(int sig);
void						sig_segv(int sig);

/*
** static.c
*/

struct termios				*get_termios(void);
struct termios				*get_newterm(void);
t_termcap					*get_termcap(void);
t_env						*get_env(void);

/*
** term.c
*/

void						write_list_reset(t_termcap *t, char *file);
int							reset_term(t_termcap *t, int write_list);
void						open_session(void);
int							write_list_init(t_termcap *t, char *file,
							int flag_fd);
int							init_term(t_termcap *t, int write_list);

/*
** termcap.c
*/

char						*look_key(t_termcap *t, char *end);

/*
** termcap_alt.c
*/

int							key_altc(t_termcap *t);
int							key_altx(t_termcap *t);
int							key_altv(t_termcap *t);
int							key_altleft(t_termcap *t);

/*
** termcap_delete.c
*/

int							key_delete(t_termcap *t);
int							key_del(t_termcap *t);

/*
** termcap_key.c
*/

int							key_altright(t_termcap *t);
int							key_right(t_termcap *t);
int							key_left(t_termcap *t);
int							key_up(t_termcap *t);
int							key_down(t_termcap *t);

/*
** termcap_other.c
*/

int							key_home(t_termcap *t);
int							key_end(t_termcap *t);
int							key_ctrld(t_termcap *t);
int							key_ret(t_termcap *t);

/*
** termcap_shift.c
*/

int							key_shup(t_termcap *t);
int							key_shdown(t_termcap *t);
int							key_shleft(t_termcap *t);
int							key_shright(t_termcap *t);

/*
** termcap_utils.c
*/

void						add_or_create_list_history(t_termcap *t, char *str);
int							compare_to_tab_key(t_termcap *t, int *found,
							char *buff);
void						add_or_create_list_start(t_list **list,
							void *content, int content_size);

/*
** tests.c
*/

int							split(char c);
int							quote(char c);
int							open_par(char c);
int							close_par(char c);
int							notonlyspace(char *str);

/*
** tree_cmd.c
*/

void						create_trees_cmd(t_termcap *t, t_env *e);

/*
** utils.c
*/

void						add_or_create_list_start(t_list **list,
							void *content, int content_size);
void						create_files(t_cmd_tree *root);
void						exec_cmd_or_builtin(t_env *e, t_fd *fd);
void						standard_cmd(t_env *e, t_cmd_tree *root, t_fd *fd);
t_token						*get_tk(t_list *list);

/*
** write.c
*/

int							ft_output(int c);
int							print_error(char *err);
void						rewrite_cmd(t_termcap *t);
void						print_char(t_termcap *t, char c);

/*
** tab_manipulation.c
*/

void						free_strtab(char **tab);
int							strtablen(char **tab);
char						**tab_add_end(char **src, char **toadd);
char						**tabjoin(char **tab1, char **tab2, int index,
							int k);

#endif
