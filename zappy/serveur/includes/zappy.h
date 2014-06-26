/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 10:09:51 by ypringau          #+#    #+#             */
/*   Updated: 2014/06/25 13:28:18 by rbrieuc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZAPPY_H
# define ZAPPY_H

# include <sys/select.h>
# include <libft.h>

# define MAX_RESOURCE_TILE	12

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define BUF_SIZE 8192

# define MAX(a,b)	((a > b) ? a : b)

enum				e_orientation
{
	NORD = 1,
	EST,
	SUD,
	OUEST
};

typedef struct		s_env
{
	int				port;
	int				width;
	int				height;
	int				max_client;
	float			time;
	int				***map;
	t_list			*teams;
	t_list			*cmds;
	t_list			*eggs;
}					t_env;

typedef struct		s_fd
{
	int				type;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read[BUF_SIZE + 1];
	char			buf_write[BUF_SIZE + 1];
}					t_fd;

typedef struct		s_net
{
	t_fd			*fds;
	int				port;
	int				maxfd;
	int				max;
	int				r;
	int				fd_graphic;
	fd_set			fd_read;
	fd_set			fd_write;
}					t_net;

typedef struct		s_team
{
	int				max;
	char			*name;
	t_list			*players;
}					t_team;

typedef struct		s_player
{
	int				id;
	int				x;
	int				y;
	int				orientation;
	int				level;
	int				inventory[7];
	unsigned long	time;
	char			*team;
}					t_player;

typedef struct		s_cmd
{
	char			*msg;
	int				fd;
	unsigned long	time;
}					t_cmd;

typedef struct		s_egg
{
	int				id;
	int				x;
	int				y;
	int				player;
	char			*team;
	int				hatched;
	unsigned long	time;
}					t_egg;

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

void				usage(char **av);
void				parse_options(t_env *e, char **av);
void				init(t_env *e);
void				init_net(t_net *net);
void				display_map(t_env *e);
void				error(char *msg);
void				srv_create(t_net *net, int port);
void				client_read(t_env *e, t_net *net, int cs);
void				client_write(t_env *e, t_net *net, int cs);
void				check_fd(t_env *e, t_net *net);
void				init_fd(t_net *net);
int					random_in_range(unsigned int min, unsigned int max);
void				display_list(t_list *list);
t_player			*new_player(t_env *e, char *team, t_pos *pos, int cs);
t_team				*new_team(t_env *e, char *name);
void				welcome(t_env *e, t_net *net, int cs);
void				gfx_commands(t_env *e, t_net *net, int cs);
int					player_action(t_env *e, t_net *net, int cs);
void				create_player(t_env *e, t_net *net, int cs);
t_player			*get_player(t_list *list, int id);
t_player			*get_player_at_pos(t_list *list, int x, int y, int id);
void				send_map(t_env *e, int cs, float delay);
int					required_incantation(t_env *e, int x, int y, int lvl);
int					get_numb_player_at(t_list *list, int x, int y, int lvl);
t_player			*get_player_at_pos_level(t_list *list, int x, int y,
					int lvl);
void				delete_player(t_list *list, int id);
t_cmd				*new_cmd(char *msg, int fd, unsigned long time);
void				del_elem_list(t_list **begin, t_list *to_del);
void				ft_lstadd_or_create(t_env *e, char *msg, int fd,
					float time);
void				forward(t_player *player, t_env *e, t_net *net);
void				right(t_player *player, t_env *e, t_net *net);
void				left(t_player *player, t_env *e, t_net *net);
int					get_player_pos_voir(t_list *list, int x, int y, int id);
t_egg				*new_egg(t_env *e, int id, t_player player);
void				broadcast(t_player *player, t_env *e, t_net *net);
void				take(t_player *player, t_env *e, t_net *net);
void				put(t_player *player, t_env *e, t_net *net);
void				fork_client(t_player *player, t_env *e, t_net *net);
void				connect_nbr(t_player *player, t_env *e, t_net *net);
void				see(t_player *player, t_env *e, t_net *net);
void				inventory(t_player *player, t_env *e, t_net *net);
void				eject(t_player *player, t_env *e, t_net *net);
void				incantation(t_player *player, t_env *e, t_net *net);
void				init_pos(t_player *player, int *x, int *y, int i);
void				compute_rows(t_env *e, t_player *player, char *msg, int i);
void				correct_pos(t_env *e, int *x, int *y);
void				init_env(t_env *e);
int					incantation_lvl_1(t_env *e, int x, int y);
int					incantation_lvl_2(t_env *e, int x, int y);
int					incantation_lvl_3(t_env *e, int x, int y);
int					incantation_lvl_4(t_env *e, int x, int y);
int					incantation_lvl_5(t_env *e, int x, int y);
int					incantation_lvl_6(t_env *e, int x, int y);
int					incantation_lvl_7(t_env *e, int x, int y);
void				lose_life(t_list *list, t_env *e, t_net *net,
					unsigned long time);
void				egg_hatching(t_env *e, t_list *head, t_net *net,
					unsigned long time);
void				send_map(t_env *e, int cs, float delay);
void				send_teams(t_list *list, int cs);
int					get_k(t_env *e, t_player *player, t_player *client);
int					casematch1(t_player *player);
int					casematch2(t_player *player);
int					casematch3(t_player *player);
int					casematch4(t_player *player);
int					casematch5(t_player *player);
int					casematch6(t_player *player);
int					casematch7(t_player *player);
int					casematch8(t_player *player);
int					casematch9(t_player *player);
int					casematch10(t_player *player);
int					casematch11(t_player *player);
int					casematch12(t_player *player);
int					casematch13(t_player *player);
int					casematch14(t_player *player);
#endif
