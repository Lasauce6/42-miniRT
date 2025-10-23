/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:37:03 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 15:33:35 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	push_object(t_obj *obj, t_obj **objs)
{
	t_obj	*tmp;

	if (!(*objs))
		*objs = obj;
	else
	{
		tmp = *objs;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
}

t_obj	*create_object(t_data *data, t_obj_id id)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (obj == NULL)
		return (NULL);
	obj->id = id;
	obj->next = NULL;
	push_object(obj, &data->objs);
	return (obj);
}

void	free_objects(t_obj **objs)
{
	t_obj	*tmp;
	t_obj	*obj;

	obj = *objs;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	*objs = 0;
}

t_rgb	get_obj_color(t_obj *obj)
{
	if (obj->id == plane)
		return (obj->object.plane.color);
	if (obj->id == sphere)
		return (obj->object.sphere.color);
	if (obj->id == cylinder)
		return (obj->object.cylinder.color);
	return (get_color(0, 0, 0));
}
