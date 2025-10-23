/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:49:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/21 12:06:33 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	parse_ambient_light(char **tokens, t_data *data)
{
	t_ambient_light	l;

	if (ft_tablen(tokens) != 3)
		return (1); // TODO: error message
	if (data->ambient.id == ambient_light)
		return (1); // TODO: error message
	if (parse_color(tokens[2], &l.color))
		return (1); // TODO: error message
	if (parse_double(tokens[1], &l.ratio))
		return (1); // TODO: error message
	l.id = ambient_light;
	data->ambient = l;
	return (0);
}

int	parse_light(char **tokens, t_data *data)
{
	t_light	*l;

	l = malloc(sizeof(t_light));
	if (l == NULL)
		return (1); // TODO: error message
	l->next = NULL;
	if (ft_tablen(tokens) != 4)
		return (free(l), 1); // TODO: error message
	if (parse_vector(tokens[1], &l->coords))
		return (free(l), 1); // TODO: error message
	if (parse_double(tokens[2], &l->ratio))
		return (free(l), 1); // TODO: error message
	if (parse_color(tokens[3], &l->color))
		return (free(l), 1); // TODO: error message
	if (data->light == NULL)
		data->light = l;
	else
	{
		l->next = data->light;
		data->light = l;
	}
	return (0);
}

void	calculate_px00_loc(t_camera *cam, t_vec *axisW)
{
	t_vec	vp_up_left;
	t_vec	half_u;
	t_vec	half_v;
	t_vec	px_half;

	half_u = vec_div_scalar(&cam->vp_u, 2.0);
	half_v = vec_div_scalar(&cam->vp_v, 2.0);
	vp_up_left = vec_sub(&cam->coords, axisW);
	vp_up_left = vec_sub(&vp_up_left, &half_u);
	vp_up_left = vec_sub(&vp_up_left, &half_v);
	px_half = vec_add(&cam->px_dlt_u, &cam->px_dlt_v);
	px_half = vec_mul_scalar(&px_half, 0.5);
	cam->px00_loc = vec_add(&vp_up_left, &px_half);
}

void	calculate_viewport(t_camera *cam)
{
	t_vec	axis[3];

	cam->focal_len = 1.0;
	cam->vp_w = 2.0 * tan(deg2rad(cam->fov) / 2);
	cam->vp_h = cam->vp_w * ((double) HEIGHT / (double) WIDTH);
	cam->center = cam->coords;
	cam->vup = vector(0, 1, 0);
	axis[2] = vec_mul_scalar(&cam->orient, -1);
	if (fabs(vec_dot_product(&cam->vup, &axis[2])) == 1)
		axis[2].x += 0.001;
	axis[0] = vec_cross_product(&cam->vup, &axis[2]);
	axis[0] = normalize(&axis[0]);
	axis[1] = vec_cross_product(&axis[2], &axis[0]);
	cam->vp_u = vec_mul_scalar(&axis[0], cam->vp_w);
	cam->vp_v = vec_mul_scalar(&axis[1], -1);
	cam->vp_v = vec_mul_scalar(&cam->vp_v, cam->vp_h);
	cam->px_dlt_u = vec_div_scalar(&cam->vp_u, WIDTH);
	cam->px_dlt_v = vec_div_scalar(&cam->vp_v, HEIGHT);
	axis[2] = vec_mul_scalar(&axis[2], cam->focal_len);
	calculate_px00_loc(cam, &axis[2]);
}

int	parse_camera(char **tokens, t_data *data)
{
	t_camera	c;

	if (data->camera.id == camera)
		return (1); // TODO: error message
	if (ft_tablen(tokens) != 4)
		return (1); // TODO: error message
	c.id = camera;
	if (parse_vector(tokens[1], &c.coords))
		return (1); // TODO: error message
	if (parse_vector(tokens[2], &c.orient))
		return (1);
	if (parse_ulong(tokens[3], &c.fov))
		return (1); // TODO: error message
	calculate_viewport(&c);
	data->camera = c;
	return (0);
}
