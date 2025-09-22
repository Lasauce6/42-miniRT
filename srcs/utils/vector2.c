/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:18:45 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/17 10:20:19 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	*normalize(t_vec *v)
{
	float	norm;

	norm = 1 / veclen(*v);
	v->x *= norm;
	v->y *= norm;
	v->z *= norm;
	return (v);
}
