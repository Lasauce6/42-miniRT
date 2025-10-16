/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:32:26 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 13:35:41 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	ray_at(t_ray ray, double t)
{
	t_vec	tmp;

	tmp = vec_mul_scalar(ray.dir, t);
	return (vec_add(ray.origin, tmp));
}

t_ray	new_ray(t_vec origin, t_vec dir)
{
	t_ray	new;

	new.origin = vector(origin.x, origin.y, origin.z);
	new.dir = vector(dir.x, dir.y, dir.z);
	return (new);
}
