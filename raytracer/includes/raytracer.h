/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypringau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/10 14:50:47 by ypringau          #+#    #+#             */
/*   Updated: 2014/03/27 22:09:29 by ypringau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# define WIN_WIDTH 640
# define WIN_HEIGHT 360
# define FOV 45
# define REFLECTION 5
# define RAY_SHADOW 25

# include <libft.h>

enum			e_type
{
	SPHERE,
	PLANE,
	CUBE,
	CYLINDER,
	CONE,
	NONE,
	SPOT,
	POINT
};

typedef struct	s_var
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
	double		f;
	double		g;
	double		h;
	double		i;
	double		j;
	double		k;
}				t_var;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_coord
{
	double		x;
	double		y;
	double		z;
}				t_coord;

typedef struct	s_img
{
	void		*ptr;
	char		*data;
	int			sizeline;
	int			bpp;
	int			endian;
	t_color		c;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct	s_sphere
{
	t_coord		position;
	t_coord		rotation;
	double		radius;
	double		height;
	int			caps;
}				t_sphere;

typedef struct	s_plane
{
	t_coord		position;
	t_coord		rotation;
	double		height;
	double		width;
	double		radius;
}				t_plane;

typedef struct	s_cube
{
	t_coord		position;
	double		height;
	double		depth;
	double		width;
	t_coord		rotation;
}				t_cube;

typedef struct	s_cylinder
{
	t_coord		position;
	t_coord		rotation;
	double		height;
	double		radius;
	int			caps;
}				t_cylinder;

typedef struct	s_cone
{
	t_coord		position;
	double		height;
	double		radius;
	t_coord		rotation;
	int			caps;
}				t_cone;

typedef struct	s_light
{
	int			type;
	t_coord		position;
	t_coord		rotation;
	t_color		color;
	double		intensity;
}				t_light;

typedef struct	s_camera
{
	t_coord		position;
	t_coord		rotation;
}				t_camera;

typedef struct	s_ray
{
	t_coord		vector;
	t_coord		origin;
}				t_ray;

typedef struct	s_material
{
	double		ambiant;
	double		diffuse;
	double		specular;
	double		phong;
	double		transparency;
	double		reflection;
	double		refraction;
	t_color		color;
}				t_material;

typedef struct	s_object
{
	int			type;
	void		*object;
	t_material	material;
}				t_object;

typedef struct	s_env
{
	int			debug;
	t_mlx		mlx_info;
	t_camera	camera;
	t_list		*objects;
	t_list		*lights;
	t_coord		view;
	t_img		img;
	t_pos		pos;
	int			direction;
	int			face;
	int			in;
	double		*mx;
	double		*my;
	t_ray		spot;
}				t_env;

typedef struct	s_getcolor
{
	t_object	*ignore;
	t_object	*current;
	int			i;
}				t_getcolor;

typedef struct	s_reftrans
{
	t_object	*object;
	t_ray		ray_save;
	t_ray		ray_tmp;
	t_ray		ray;
	t_getcolor	gc;
	double		t;
}				t_reftrans;

typedef struct	s_vlight
{
	t_object	*object;
	t_color		*col;
	t_color		old;
}				t_vlight;

typedef struct	s_min
{
	t_ray		raymin;
	double		tmin;
	double		dmin;
	t_object	*objectmin;
}				t_min;

void			add_or_create_list(t_list **addto, void *toadd, int size);
int				parse_objects_line(t_env *e, char *line, int *ii, int fd);
void			file_error(int type, char *info1, char *info2);
int				parse_position(char *str, t_coord *pos);
int				parse_rotation(char *str, t_coord *rot);
int				parse_color(char *str, t_color *c);
int				not_double(char *str);
int				parse_size(char *str, double *size);
int				parse_item(int fd, t_env *e, char *line,
				int (*f)(t_env *, char *, int *, int fd));
int				parse_lights_line(t_env *e, char *line, int *i, int fd);
int				parse_material_line(t_env *e, char *line, int *i, int fd);
void			init_parser(t_env *e, int ac, char **av);
t_coord			vectorize(t_coord a, t_coord b);
double			norm_vect(t_coord vector);
double			dot_product(t_coord a, t_coord b);
t_coord			normalize(t_coord vect);
t_coord			pt_inter(t_ray ray, double t);
void			light(t_env *e, t_color *col, t_coord inter, t_reftrans rt);
void			calculate_normal(t_env *e, t_coord *normal,
				t_object *object, t_coord inter);
double			intersection_sphere(t_env *e, t_sphere *sphere, t_ray ray);
double			intersection_cylinder(t_env *e, t_cylinder *cylinder,
				t_ray ray);
double			intersection_plane(t_env *e, t_plane *plane, t_ray ray);
double			intersection_cone(t_env *e, t_cone *cone, t_ray ray);
double			intersection_cube(t_env *e, t_cube *cube, t_ray ray);
void			draw(t_env *e);
void			apply_rotation(t_coord *rotation, t_coord *normal);
int				check_intersec_light(double *intersec, t_coord inter,
				t_ray spot);
void			adjust_color(t_color *new_color);
void			test_objects(t_env *e, t_list *objects, t_ray *spot,
				double *t);
double			check_min(double delta, double a, double b, double c);
void			debug(t_color *col, t_object *object);
void			init_ray(t_env *e, t_ray *ray);
void			init_view(t_env *e);
double			check_min(double delta, double a, double b, double c);
void			mlx_put_pixel_to_image(t_env *e, int x, int y, t_color *c);
int				parse_cone(t_env *e, char *line, int *i, int fd);
int				parse_cylinder(t_env *e, char *line, int *i, int fd);
int				parse_plane(t_env *e, char *line, int *i, int fd);
int				parse_sphere(t_env *e, char *line, int *i, int fd);
int				parse_cube(t_env *e, char *line, int *i, int fd);
t_cone			*new_cone(void);
t_cylinder		*new_cylinder(void);
t_plane			*new_plane(void);
t_cube			*new_cube(void);
t_sphere		*new_sphere(void);
t_light			*new_light(int type);
void			trim_to_double_point(char **tmp);
int				parse_cam_line(t_env *e, char *line, int *i, int fd);
int				parse_rotation(char *str, t_coord *rot);
int				parse_position(char *str, t_coord *pos);
int				parse_size(char *str, double *size);
int				parse_color(char *str, t_color *c);
int				not_int(char *str);
int				not_double(char *str);
int				parse_light_line_item(t_env *e, char **tab, int fd);
int				parse_light(t_env *e, char *line, int *i, int fd);
double			check_min(double delta, double a, double b, double c);
double			get_max(double delta, double a, double b, double c);
double			caps_cone(t_cone *cone, t_ray ray, double min, double max);
double			caps_cylinder(t_cylinder *cylinder, t_ray ray, double min,
				double max);
double			caps_sphere(t_sphere *sphere, t_ray ray, double min,
				double max);
void			ambiant(t_color *new_color, t_color old, t_object *object);
void			diffuse(t_color *new_color, t_color old, t_object *object,
				double diff);
void			specular(t_vlight *vl, t_ray spot, t_coord normal);
void			create_mat_shadow(t_env *e);
double			*get_matrix(t_object *object);
t_object		*intersection_refl(t_list *objects, t_object *object,
				t_env *e, double *t, t_ray *ray);
double			*trans_matrix(double *m);
t_coord			transf_point(t_coord point, double *matrix);
t_ray			transf_ray(t_ray ray, double *matrix);
void			print_matrix(double *matrix);
double			*invert_matrix(double *matrix);
double			*transf_matrix(t_coord rotation, t_coord translation);
double			*cross_matrix(double *m1, double *m2);
t_coord			transf_vector(t_coord vector, double *matrix);
t_coord			calc_reflection(t_coord normal, t_coord vector);
t_coord			calc_transparency(t_coord normal, t_coord vector,
				double sqroot, double n);
void			calc_color(t_color *col, t_color *col2, t_color old,
				double coef);
double			shadows(t_env *e, t_list *objects, t_coord inter);
void			get_color(t_env *e, t_ray ray, t_color *col, t_getcolor gc);
t_object		*intersection(t_list *objects, t_env *e, t_reftrans *rt);

#endif

