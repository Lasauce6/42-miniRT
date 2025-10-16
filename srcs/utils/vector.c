/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:13:45 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 17:46:07 by rbaticle         ###   ########.fr       */
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

float	vec_dist(t_vec v1, t_vec v2)
{
	return (veclen(vec_sub(v1, v2)));
}

t_vec	normalize(t_vec v)
{
	float	norm;

	norm = 1 / veclen(v);
	v.x *= norm;
	v.y *= norm;
	v.z *= norm;
	return (v);
}
