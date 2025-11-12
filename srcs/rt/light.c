/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jili <jili@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:18:36 by rbaticle          #+#    #+#             */
/*   Updated: 2025/11/12 13:17:28 by jili             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static double	calculate_light(t_vec pos, t_vec point, t_data *data,
			t_hit *rec)
{
	t_ray	light;
	double	magnitude;
	double	dotprod;
	t_hit	light_rec;

	light.origin = pos;
	light.dir = vec_sub(&light.origin, &point);
	magnitude = veclen(&light.dir);
	light.dir = vec_sub(&point, &light.origin);
	light.dir = normalize(&light.dir);
	light_rec = nearest_hit(&light, data);
	light.dir = vec_sub(&light.origin, &point);
	light.dir = normalize(&light.dir);
	if (light_rec.t > 0.0 && light_rec.t + 1e-1 < magnitude)
		dotprod = -1.0;
	else
		dotprod = vec_dot_product(&rec->normal, &light.dir);
	return (dotprod);
}

static int	ft_max(int val1, int lim)
{
	if (val1 >= lim)
		return (lim);
	return (val1);
}

static t_rgb	add_color(t_rgb col1, t_rgb col2)
{
	col1.r = ft_max(col1.r + col2.r, 255);
	col1.g = ft_max(col1.g + col2.g, 255);
	col1.b = ft_max(col1.b + col2.b, 255);
	col1.hex = (col1.r << 16) + (col1.g << 8) + col1.b;
	return (col1);
}

t_rgb	illuminate(t_data *data, t_vec point, t_hit *rec)
{
	double	dotprod;
	t_rgb	final;
	t_rgb	illum;
	t_light	*lightptr;

	final = mix_color(data->ambient.color, get_obj_color(rec->obj),
			data->ambient.ratio);
	lightptr = data->light;
	while (lightptr)
	{
		dotprod = calculate_light(lightptr->coords, point, data, rec);
		if (dotprod > 0.0)
		{
			illum = mix_color(lightptr->color, get_obj_color(rec->obj),
					dotprod * lightptr->ratio);
			final = add_color(final, illum);
		}
		lightptr = lightptr->next;
	}
	return (final);
}
