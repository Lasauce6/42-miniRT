/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:31:10 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 17:45:15 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_rgb	ray_color(t_ray *ray, t_data *data)
{
	t_hit	rec;
	t_rgb	px_color;

	rec = nearest_hit(ray, data);
	if (rec.t > 0)
	{
		px_color = illuminate(data, ray_at(*ray, rec.t), &rec);
		return (px_color);
	}
	return (mix_color(data->ambient.color, get_color(100, 100, 100), 0.4));
}

double	rand_number(void)
{
	double	val;
	int		readval;

	if (SAMPLES == 1)
		return (0.5);
	readval = rand();
	if (readval < 0)
		readval *= -1;
	val = (double)readval;
	while (val >= 1)
		val /= 10;
	return (val);
}

t_vec	rand_pixel(t_vec deltu, t_vec deltv)
{
	t_vec	tempx;
	t_vec	tempy;

	tempx = vec_mul_scalar(deltu, -0.5 + rand_number());
	tempy = vec_mul_scalar(deltv, -0.5 + rand_number());
	return (vec_add(tempx, tempy));
}

t_vec	camera_ray(t_data *data, int i, int j)
{
	t_vec	px_position[3];
	t_vec	px_center;
	t_vec	ray_dir;
	t_vec	px_samp;
	t_ray	ray;

	px_position[0] = vec_mul_scalar(data->camera.px_dlt_u, i);
	px_position[1] = vec_mul_scalar(data->camera.px_dlt_v, j);
	px_position[2] = vec_add(px_position[0], px_position[1]);
	px_center = vec_add(data->camera.px00_loc, px_position[2]);
	px_position[0] = rand_pixel(data->camera.px_dlt_u, data->camera.px_dlt_v);
	px_samp = vec_add(px_center, px_position[0]);
	ray_dir = vec_sub(px_samp, data->camera.center);
	ray = new_ray(data->camera.center, ray_dir);
	return (color_to_vec(ray_color(&ray, data)));
}

void	cast_rays(t_data *data)
{
	int		i;
	int		j;
	int		samp;
	t_vec	pt;
	t_vec	pt2;

	j = 0;
	while (++j < HEIGHT)
	{
		i = 0;
		while (++i < WIDTH)
		{
			pt2 = vector(0, 0, 0);
			samp = -1;
			while (++samp < SAMPLES)
			{
				pt = camera_ray(data, i, j);
				pt2 = vec_add(pt, pt2);
			}
			my_mlx_pixel_put(data, i, j, average_color(pt2));
		}
	}
}
