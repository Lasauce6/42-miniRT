/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:09:54 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 19:46:37 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	vec_add(t_vec *v1, t_vec *v2)
{
	return (vector(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z));
}

t_vec	vec_sub(t_vec *v1, t_vec *v2)
{
	return (vector(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

double	vec_dot_product(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec	vec_cross_product(t_vec *v1, t_vec *v2)
{
	t_vec	res;

	res = vector((v1->y * v2->z) - (v1->z * v2->y),
			(v1->z * v2->x) - (v1->x * v2->z),
			(v1->x * v2->y) - (v1->y * v2->x));
	return (res);
}
