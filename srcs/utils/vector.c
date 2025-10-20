/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:13:45 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 19:58:41 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	vector(float x, float y, float z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double	veclen(t_vec *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

t_vec	normalize(t_vec *v)
{
	t_vec	new;
	double	len;
	double	inv_len;

	new = vector(v->x, v->y, v->z);
	len = veclen(&new);
	if (len > 0)
	{
		inv_len = 1.0 / len;
		new.x = v->x * inv_len;
		new.y = v->y * inv_len;
		new.z = v->z * inv_len;
	}
	return (new);
}
