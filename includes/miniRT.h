/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:13:06 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/15 17:04:20 by rbaticle         ###   ########.fr       */
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

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef enum e_obj_id
{
	ambient_light,
	camera,
	light,
	sphere,
	plane,
	cylinder,
}	t_obj_id;

typedef struct s_ambient_light
{
	t_obj_id	id;
	float		ratio;
	int			color;
}	t_ambient_light;

typedef struct s_camera
{
	t_vec	coords;
	t_vec	orient;
	size_t	fov;
	float	scale;
}	t_camera;

typedef struct s_light
{
	t_vec			coords;
	float			ratio;
	int				color;
	struct s_light	*next;
}	t_light;

typedef struct s_sphere
{
	t_vec	coords;
	float	diam;
	int		color;
}	t_sphere;

typedef struct s_plane
{
	t_vec	coords;
	t_vec	vect;
	int		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	coords;
	t_vec	axis;
	float	diam;
	float	height;
	int		color;
}	t_cylinder;

typedef union u_obj
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_obj_union;

typedef struct s_obj
{
	t_obj_id		id;
	t_obj_union		object;
	struct s_obj	*next;
}	t_obj;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	void			*mlx_ptr;
	void			*win;
	t_camera		camera;
	t_ambient_light	ambient;
	t_light			*light;
	t_obj			*objs;
}	t_data;

// ## Parsing ##
// parse_light.c
int	parse_file(char *filename, t_data *data);
int	parse_ambient_light(char **tokens, t_data *data);
// parse_utils.c
int	parse_vector(char *str, t_vec *vec);
int	parse_color(char *str, int *color);
int	parse_float(char *str, float *fl);

// ## Utils ##
// get_color.c
int	get_color(int r, int g, int b);
int	get_r(int color);
int	get_g(int color);
int	get_b(int color);
// numbers.c
int	is_float(char *str);
int	is_ulong(char *str);

#endif
