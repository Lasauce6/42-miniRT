/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:20:53 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 14:34:34 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	vec_mul_scalar(t_vec v, double t)
{
	v.x *= t;
	v.y *= t;
	v.z *= t;
	return (v);
}

t_vec	vec_div_scalar(t_vec v, double t)
{
	v.x /= t;
	v.y /= t;
	v.z /= t;
	return (v);
}

t_vec	unitary_vector(t_vec v)
{
	return (vec_div_scalar(v, veclen(v)));
}

double	veclen_squared(t_vec vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
