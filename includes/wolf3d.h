/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prenvois <prenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/31 18:19:54 by prenvois          #+#    #+#             */
/*   Updated: 2014/01/19 18:40:10 by prenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <libft.h>
# include <sys/time.h>

# define WW 1280
# define WH 720

# define UP keycode == 119 || keycode == 65362
# define LEFT keycode == 97 || keycode == 65361
# define DOWN keycode == 115 || keycode == 65364
# define RIGHT keycode == 100 || keycode == 65363
# define SPRINT keycode == 65505
# define ESC keycode == 65307
# define RESET keycode == 114
# define SPACE keycode == 32

int				g_pidfather;

typedef struct	s_move
{
	double		speed;
	double		rot;
	int			sprint;
	int			up;
	int			down;
	int			right;
	int			left;
	int			space;
	int			reset;
}				t_move;

typedef struct	s_var
{
	double		posx;
	double		posy;
	double		odirx;
	double		dirx;
	double		diry;
	double		ospanx;
	double		spanx;
	double		spany;
	double		camx;
	double		rayx;
	double		rayy;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		ddistx;
	double		ddisty;
	double		pwalldist;
	int			stepx;
	int			stepy;
	int			side;
	double		wallx;
}				t_var;

typedef struct	s_img
{
	void		*img;
	char		*data;
	int			bpp;
	int			lsize;
	int			endian;
}				t_img;

typedef struct	s_texwall
{
	void		*tex;
	void		*texdoor;
	void		*texscrt;
	void		*texkeys;
	void		*texintro;
	void		*texblock;
	void		*textip;
	void		*texend;
	void		*texarrow;
	void		*texportal;
	void		*texanti;
	void		*texstanley;
	void		*texqube;
	char		*data;
	int			bpp;
	int			lsize;
	int			endian;
	int			w;
	int			h;
	int			texx;
	int			texy;
	int			d;
	int			stripeheight;
	int			stripestart;
	int			stripeend;
}				t_texwall;

typedef struct	s_texfloor
{
	void		*tex;
	char		*data;
	int			bpp;
	int			lsize;
	int			endian;
	int			w;
	int			h;
	int			texx;
	int			texy;
}				t_texfloor;

typedef struct	s_colors
{
	int			wr;
	int			wg;
	int			wb;
}				t_colors;

typedef struct	s_floor
{
	double		floorx;
	double		floory;
	double		walldist;
	double		camdist;
	double		dist;
	double		weight;
	double		curx;
	double		cury;
}				t_floor;

typedef struct		s_fps
{
	size_t			oldtime;
	size_t			now;
	double			fps;
	double			frametime;
	long			usec;
	long			sec;
	struct timeval	time;
}					t_fps;

typedef struct		s_misc
{
	int				c;
	int				reset;
	int				action;
	struct timeval	score;
	long			ssec;
	long			esec;
	int				fmn;
	long			fsec;
}					t_misc;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	int				**map;
	t_colors		c;
	t_img			i;
	t_texwall		tw;
	t_texfloor		tf;
	t_var			v;
	t_move			m;
	t_floor			f;
	t_fps			fps;
	t_misc			misc;
}					t_env;

/*
** utils.c
*/
void			mlx_check(void *data);
void			fps(t_env *e);
void			init_var_n_inputs(t_env *e);
void			init_textures(t_env *e);

/*
** utils2.c
*/
void			display_score(t_env *e);
void			check_triggers(t_env *e);

/*
** utils3.c
*/
void			stock_map(t_env *e);
void			rand_color(t_env *e);
void			set_music(char ***tab);

/*
** check_inputs.c
*/
void			check_inputs(t_env *e);
void			reset(t_env *e);

/*
** draw.c
*/
void			draw_img(int x, t_env *e);

/*
** draw_utils.c
*/
void			floorcasting(t_env *e);
void			select_texture(int x, t_env *e);

/*
** raycasting.c
*/
void			raycasting(int x, t_env *e);

/*
** wolf3d.c
*/
int				main(void);
#endif /* !WOLF3D_H */
