/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:49:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/11/05 11:34:05 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	parse_ambient_light(char **tokens, t_data *data)
{
	t_ambient_light	l;

	if (ft_tablen(tokens) != 3)
		//return (1); // DONE: error message
		return(error_failure(STR_ERR_FILE_INFO, NULL));
	if (data->ambient.id == ambient_light)
		//return (1); // DONE: error message
		return(error_failure(STR_ERR_DUP, NULL));
	if (parse_color(tokens[2], &l.color))
		//return (1); // DONE: error message
		return(error_failure(STR_ERR_PARSER_COLOR, tokens[2]));
	if (parse_double(tokens[1], &l.ratio, RATIO))
		//return (1); // DONE: error message
		return(error_failure(STR_ERR_PARSER_DOUBLE, tokens[1]));
	l.id = ambient_light;
	data->ambient = l;
	return (0);
}

int	parse_light(char **tokens, t_data *data)
{
	t_light	*l;

	l = malloc(sizeof(t_light));
	if (l == NULL)
		//return (1); // DONE: error message
		error_failure(STR_ERR_MALLOC, NULL);
	l->next = NULL;
	if (ft_tablen(tokens) != 4)
		error_failure_free_light(STR_ERR_FILE_INFO, NULL, l);
		//return (free(l), 1); // DONE: error message 
	if (parse_vector(tokens[1], &l->coords, VECTOR))
		//return (free(l), 1); // DONE: error message
		error_failure_free_light(STR_ERR_PARSER_VECTOR, tokens[1], l);
	if (parse_double(tokens[2], &l->ratio, RATIO))
		//return (free(l), 1); // DONE: error message
		error_failure_free_light(STR_ERR_PARSER_DOUBLE, tokens[2], l);
	if (parse_color(tokens[3], &l->color))
		//return (free(l), 1); // DONE: error message
		error_failure_free_light(STR_ERR_PARSER_COLOR, tokens[3], l);
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

	cam->focal_len = 1.0;// WHY : La distance focale par défaut est-elle de 1.0 ?
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
		//return (1); // DONE: error message
		error_failure(STR_ERR_DUP, NULL);
	if (ft_tablen(tokens) != 4)
		//return (1); // DONE: error message
		error_failure(STR_ERR_FILE_INFO, NULL);
	c.id = camera;
	if (parse_vector(tokens[1], &c.coords, VECTOR))
		//return (1); // DONE: error message
		error_failure(STR_ERR_PARSER_VECTOR, tokens[1]);
	if (parse_vector(tokens[2], &c.orient, NORMAL))
		//return (1);
		error_failure(STR_ERR_PARSER_VECTOR, tokens[2]);
	if (parse_ulong(tokens[3], &c.fov, FOV))//WHY : unsigned long? why not int?
		//return (1); // DONE: error message
		error_failure(STR_ERR_PARSER_ULONG, tokens[3]);
	calculate_viewport(&c);
	data->camera = c;
	return (0);
}
