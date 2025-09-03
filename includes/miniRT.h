/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:13:06 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/03 15:57:14 by rbaticle         ###   ########.fr       */
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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx_ptr;
	void	*win;
}	t_data;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ambiant_light
{
	float	ratio;
	int		color;
}	t_ambiant_light;

typedef struct s_camera
{
	t_vec	coords;
	t_vec	orient;
	size_t	fov;
	float	scale;
}	t_camera;

// Parsing
int	parse_file(char *filename, t_data *data);
int	parse_ambiant_light(char **tokens, t_data *data);

// Utils
int	get_color(int r, int g, int b);
int	get_r(int color);
int	get_g(int color);
int	get_b(int color);

#endif
