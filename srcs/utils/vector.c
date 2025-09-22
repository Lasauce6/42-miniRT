/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:13:45 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/17 10:18:33 by rbaticle         ###   ########.fr       */
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

float	veclen(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = b.x - a.x;
	res.y = b.y - a.y;
	res.z = b.y - a.y;
	return (res);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = b.x + a.x;
	res.y = b.y + a.y;
	res.z = b.z + a.z;
	return (res);
}

t_vec	vec_mul(t_vec v, float f)
{
	t_vec	res;

	res.x = v.x * f;
	res.y = v.y * f;
	res.z = v.z * f;
	return (res);
}
