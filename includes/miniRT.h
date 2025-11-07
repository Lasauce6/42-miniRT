/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jili <jili@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:13:06 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/24 16:04:56 by jili             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx-linux/mlx.h"

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>

# define WIDTH 1500
# define HEIGHT 1000
# define MIN 1
# define MAX 2

// ## Nb samples for supersampling ##
# define SAMPLES 1

// ## Hit cylinder ##
# define BODY 0
# define BOT 1
# define TOP 2


// ## error and free

# define STR_PROG_NAME "miniRT"
# define STR_USAGE "%s usage: <file.rt>.\n "
# define STR_OPEN "%s invalid input : %s open failed. \n"
# define STR_ERR_INPUT "%s is not a valid file.rt.\n"
# define STR_ERR_FILE_INFO "%s invalid input: The information about one element is incorrect.\n"
# define STR_ERR_PARSER_VECTOR "%s invalid input: Could not parser the vector %s.\n"
# define STR_ERR_PARSER_DOUBLE "%s invalid input: Could not parser the double %s.\n"
# define STR_ERR_PARSER_ULONG "%s invalid input: Could not parser the unsigned long %s.\n "
# define STR_ERR_PARSER_COLOR "%s invalid input: Could not parser the color %s.\n"
# define STR_ERR_MISSING_ELE "%s invalid input: Missing one element.\n"
# define STR_ERR_DUP "%s invalid input: Element duplication.\n"
# define STR_ERR_MALLOC "%s error : Could not allocate memory.\n"
# define STR_ERR_MLX "%s mlx failed.\n"


typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	hex;
}	t_rgb;

typedef enum e_obj_id
{
	ambient_light,
	camera,
	light,
	sphere,
	plane,
	cylinder,
	null,
}	t_obj_id;

typedef struct s_ambient_light
{
	t_obj_id	id;
	double		ratio;
	t_rgb		color;
}	t_ambient_light;

typedef struct s_camera
{
	t_obj_id	id;
	t_vec		coords;
	t_vec		orient;
	size_t		fov;
	double		vp_h;
	double		vp_w;
	double		focal_len;
	t_vec		center;
	t_vec		vp_u;
	t_vec		vp_v;
	t_vec		vup;
	t_vec		px_dlt_u;
	t_vec		px_dlt_v;
	t_vec		px00_loc;
}	t_camera;

typedef struct s_light//free
{
	t_vec			coords;
	double			ratio;
	t_rgb			color;
	struct s_light	*next;
}	t_light;

typedef struct s_sphere
{
	t_vec	pos;
	double	radius;
	t_rgb	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec	pos;
	t_vec	dir;
	t_rgb	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	pos;
	t_vec	dir;
	double	radius;
	double	height;
	t_rgb	color;
	bool	hit[3];
}	t_cylinder;

typedef struct s_disk
{
	t_vec	pos;
	t_vec	dir;
	double	rad;
}	t_disk;

typedef union u_obj
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_obj_union;

typedef struct s_obj//free
{
	t_obj_id		id;
	t_obj_union		object;
	struct s_obj	*next;
}	t_obj;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_hit_calc
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	root;
	double	sqrt;
}	t_hcalc;

typedef struct s_hit
{
	t_obj	*obj;
	t_vec	point;
	t_rgb	color;
	t_vec	normal;
	double	t;
	double	ray_tmin;
	double	ray_tmax;
}	t_hit;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	void			*mlx_ptr;
	void			*win;
	t_ray			ray;
	t_camera		camera;
	t_ambient_light	ambient;
	t_light			*light;
	t_obj			*objs;
	size_t			winsize;
	double			aspect_ratio;
}	t_data;

// main.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//mlx_utils.c
int		close_window(t_data *data);
int		key_hook(int keycode, t_data *data);

// exit.c
int		error_failure(char *format, char *detail);
int		error_failure_free_obj(char *format, char *detail, t_obj *obj);
int 	error_failure_free_light(char *format, char *detail, t_light *light);
void	*free_table(t_data *data);
int		message_error(char *format, char *detail, int exit_no);

// ## Parsing ##
// parsing.c
int		parse_file(char *filename, t_data *data);
// parse_light.c
int		parse_ambient_light(char **tokens, t_data *data);
int		parse_light(char **tokens, t_data *data);
int		parse_camera(char **tokens, t_data *data);
// parse_objects.c
int		parse_sphere(char **tokens, t_data *data);
int		parse_plane(char **tokens, t_data *data);
int		parse_cylinder(char **tokens, t_data *data);
// parse_utils.c
int		parse_vector(char *str, t_vec *vec);
int		parse_color(char *str, t_rgb *color);
int		parse_double(char *str, double *d);
int		parse_ulong(char *str, size_t *n);

// ## RT ##
// ray.c
void	cast_rays(t_data *data);
// hit.c
t_hit	nearest_hit(t_ray *ray, t_data *data);
// hit_cylinder.c
bool	hit_body_cylinder(t_ray *ray, t_cylinder cylinder, t_hit *rec);
bool	hit_disk(t_ray *ray, t_disk *disk, t_hit *rec);
// light.c
t_rgb	illuminate(t_data *data, t_vec point, t_hit *rec);

// ## Utils ##
// color.c
t_rgb	get_color(unsigned int r, unsigned int g, unsigned int b);
t_rgb	new_color_doub(double r, double g, double b);
t_rgb	mix_color(t_rgb col1, t_rgb col2, double ratio);
t_vec	color_to_vec(t_rgb col);
int		average_color(t_vec color);
// numbers.c
int		is_double(char *str);
int		is_ulong(char *str);
double	deg2rad(double deg);
double	rad2deg(double rad);
double	ft_atod(char *str);
// vector.c
t_vec	vector(float x, float y, float z);
double	veclen(t_vec *v);
t_vec	normalize(t_vec *v);
// vector2.c
t_vec	vec_add(t_vec *v1, t_vec *v2);
t_vec	vec_sub(t_vec *v1, t_vec *v2);
double	vec_dot_product(t_vec *v1, t_vec *v2);
t_vec	vec_cross_product(t_vec *v1, t_vec *v2);
// vector3.c
t_vec	vec_mul_scalar(t_vec *v, double t);
t_vec	vec_div_scalar(t_vec *v, double t);
t_vec	unitary_vector(t_vec *v);
double	veclen_squared(t_vec *vec);
// obj_utils.c
void	push_object(t_obj *obj, t_obj **objs);
t_obj	*create_object(t_data *data, t_obj_id id);
void	free_objects(t_obj **objs);
t_rgb	get_obj_color(t_obj *obj);
// ray_utils.c
t_vec	ray_at(t_ray ray, double t);
t_ray	new_ray(t_vec origin, t_vec dir);


#endif
