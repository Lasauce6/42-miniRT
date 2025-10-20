/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:12:13 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 22:19:08 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static bool	hit_plane(t_ray *ray, t_plane plane, t_hit *rec)
{
	double	denom;
	double	d;
	double	t;

	denom = vec_dot_product(&plane.dir, &ray->dir);
	if (fabs(denom) < 1e-6)
		return (false);
	d = vec_dot_product(&plane.dir, &plane.pos);
	t = (d - vec_dot_product(&plane.dir, &ray->origin)) / denom;
	if (t < rec->ray_tmin || t > rec->ray_tmax)
		return (false);
	rec->t = t;
	rec->point = ray_at(*ray, t);
	rec->normal = plane.dir;
	return (true);
}

static bool	hit_sphere(t_ray *ray, t_sphere sphere, t_hit *rec)
{
	t_hcalc	calc;
	t_vec	oc;

	oc = vec_sub(&ray->origin, &sphere.pos);
	calc.a = veclen_squared(&ray->dir);
	calc.b = vec_dot_product(&oc, &ray->dir);
	calc.c = veclen_squared(&oc) - (sphere.radius * sphere.radius);
	calc.disc = (calc.b * calc.b) - (calc.a * calc.c);
	if (calc.disc < 0)
		return (false);
	calc.sqrt = sqrt(calc.disc);
	calc.root = (-calc.b - calc.sqrt) / calc.a;
	if (calc.root <= rec->ray_tmin || rec->ray_tmax <= calc.root)
	{
		calc.root = (-calc.b + calc.sqrt) / calc.a;
		if (calc.root <= rec->ray_tmin || rec->ray_tmax <= calc.root)
			return (false);
	}
	rec->t = calc.root;
	rec->point = ray_at(*ray, rec->t);
	rec->normal = vec_sub(&rec->point, &sphere.pos);
	rec->normal = normalize(&rec->normal);
	return (true);
}

static bool	hit_cylinder(t_ray *ray, t_cylinder cylinder, t_hit *rec)
{
	t_disk	disk;
	t_ray	axis;

	axis.origin = cylinder.pos;
	axis.dir = cylinder.dir;
	disk.pos = cylinder.pos;
	disk.dir = cylinder.dir;
	disk.rad = cylinder.radius;
	cylinder.hit[BOT] = hit_disk(ray, &disk, rec);
	if (cylinder.hit[BOT])
		rec->ray_tmax = rec->t;
	disk.pos = ray_at(axis, cylinder.height);
	disk.dir = vec_mul_scalar(&cylinder.dir, -1);
	cylinder.hit[BODY] = hit_body_cylinder(ray, cylinder, rec);
	if (cylinder.hit[BODY])
		rec->ray_tmax = rec->t;
	cylinder.hit[TOP] = hit_disk(ray, &disk, rec);
	if (cylinder.hit[TOP])
		rec->ray_tmax = rec->t;
	return (cylinder.hit[BOT] || cylinder.hit[BODY] || cylinder.hit[TOP]);
}

static bool	hit_obj(t_ray *ray, t_obj *obj, t_hit *rec)
{
	if (obj->id == plane)
		return (hit_plane(ray, obj->object.plane, rec));
	if (obj->id == sphere)
		return (hit_sphere(ray, obj->object.sphere, rec));
	if (obj->id == cylinder)
		return (hit_cylinder(ray, obj->object.cylinder, rec));
	return (false);
}

t_hit	nearest_hit(t_ray *ray, t_data *data)
{
	t_obj	*obj;
	t_hit	rec;

	rec.ray_tmin = 0.0000001;
	rec.ray_tmax = INT_MAX;
	rec.t = -1.0;
	obj = data->objs;
	while (obj)
	{
		if (hit_obj(ray, obj, &rec) == true)
		{
			rec.ray_tmax = rec.t;
			rec.obj = obj;
		}
		obj = obj->next;
	}
	return (rec);
}
