/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:51:57 by rbaticle          #+#    #+#             */
/*   Updated: 2025/11/12 13:30:33 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_vec	calculate_normal(t_cylinder cylinder, t_vec point)
{
	t_vec	tmp;
	t_vec	tmp2;
	t_vec	normal;

	tmp = vec_sub(&cylinder.pos, &point);
	tmp2 = vec_mul_scalar(&cylinder.dir, vec_dot_product(&tmp, &cylinder.dir));
	normal = vec_sub(&tmp2, &tmp);
	return (unitary_vector(&normal));
}

static bool	calc_hit_cylinder(t_hcalc calc, t_ray *ray, t_cylinder cylinder,
		t_hit *rec)
{
	double	projection;
	t_vec	tmp;

	if (calc.disc < 0)
		return (false);
	calc.sqrt = sqrt(calc.disc);
	calc.root = (-calc.b - calc.sqrt) / calc.a;
	if (calc.root <= rec->ray_tmin || calc.root >= rec->ray_tmax)
	{
		calc.root = (-calc.b + calc.sqrt) / calc.a;
		if (calc.root <= rec->ray_tmin || calc.root >= rec->ray_tmax)
			return (false);
	}
	tmp = ray_at(*ray, calc.root);
	tmp = vec_sub(&tmp, &cylinder.pos);
	projection = vec_dot_product(&cylinder.dir, &tmp);
	if (projection < -cylinder.height / 2.0
		|| projection > cylinder.height / 2.0)
		return (false);
	rec->t = calc.root;
	rec->point = ray_at(*ray, calc.root);
	rec->normal = calculate_normal(cylinder, rec->point);
	if (vec_dot_product(&ray->dir, &rec->normal) > 0)
		rec->normal = vec_mul_scalar(&rec->normal, -1);
	return (true);
}

bool	hit_body_cylinder(t_ray *ray, t_cylinder cylinder, t_hit *rec)
{
	t_vec	oc;
	t_vec	tmp;
	t_vec	dir_parallel;
	t_vec	oc_parallel;
	t_hcalc	calc;

	oc = vec_sub(&ray->origin, &cylinder.pos);
	tmp = vec_mul_scalar(&cylinder.dir,
			vec_dot_product(&ray->dir, &cylinder.dir));
	dir_parallel = vec_sub(&ray->dir, &tmp);
	tmp = vec_mul_scalar(&cylinder.dir,
			vec_dot_product(&oc, &cylinder.dir));
	oc_parallel = vec_sub(&oc, &tmp);
	calc.a = veclen_squared(&dir_parallel);
	calc.b = vec_dot_product(&oc_parallel, &dir_parallel);
	calc.c = veclen_squared(&oc_parallel) - cylinder.radius * cylinder.radius;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	return (calc_hit_cylinder(calc, ray, cylinder, rec));
}

bool	hit_disk(t_ray *ray, t_disk *disk, t_hit *rec)
{
	double	denom;
	t_vec	oc;
	double	t;
	t_vec	p;
	t_vec	to_center;

	denom = vec_dot_product(&disk->dir, &ray->dir);
	if (fabs(denom) < 1e-6)
		return (false);
	oc = vec_sub(&disk->pos, &ray->origin);
	t = vec_dot_product(&oc, &disk->dir) / denom;
	if (t <= rec->ray_tmin || t >= rec->ray_tmax)
		return (false);
	p = ray_at(*ray, t);
	to_center = vec_sub(&p, &disk->pos);
	if (vec_dot_product(&to_center, &to_center) > disk->rad * disk->rad)
		return (false);
	rec->t = t;
	rec->point = p;
	rec->normal = disk->dir;
	if (vec_dot_product(&ray->dir, &rec->normal) > 0)
		rec->normal = vec_mul_scalar(&rec->normal, -1);
	return (true);
}
