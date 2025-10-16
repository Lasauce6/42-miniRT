/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:03:11 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 15:33:43 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_rgb	get_color(unsigned int r, unsigned int g, unsigned int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.hex = (color.r << 16) + (color.g << 8) + color.b;
	return (color);
}

t_rgb	new_color_doub(double r, double g, double b)
{
	t_rgb	color;

	color.r = (unsigned int)(r * 255.999);
	color.g = (unsigned int)(g * 255.999);
	color.b = (unsigned int)(b * 255.999);
	color.hex = (color.r << 16) + (color.g << 8) + color.b;
	return (color);
}

t_rgb	mix_color(t_rgb col1, t_rgb col2, double ratio)
{
	t_rgb	new;
	t_vec	dcol1;
	t_vec	dcol2;

	dcol1.x = col1.r / 255.9999;
	dcol1.y = col1.g / 255.9999;
	dcol1.z = col1.b / 255.9999;
	dcol2.x = col2.r / 255.9999;
	dcol2.y = col2.g / 255.9999;
	dcol2.z = col2.b / 255.9999;
	new = new_color_doub(dcol1.x * dcol2.x * ratio,
			dcol1.y * dcol2.y * ratio, dcol1.z * dcol2.z * ratio);
	return (new);
}

t_vec	color_to_vec(t_rgb col)
{
	t_vec	vec;

	vec.x = col.r / 255.9999;
	vec.y = col.g / 255.9999;
	vec.z = col.b / 255.9999;
	return (vec);
}

int	average_color(t_vec color)
{
	t_rgb	col;

	color.x *= 1.0 / (double) SAMPLES;
	color.y *= 1.0 / (double) SAMPLES;
	color.z *= 1.0 / (double) SAMPLES;
	col = new_color_doub(color.x, color.y, color.z);
	return (col.hex);
}
