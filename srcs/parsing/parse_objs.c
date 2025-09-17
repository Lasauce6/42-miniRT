/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:25:08 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/17 10:38:11 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	parse_plane(char **tokens, t_data *data)
{
	t_plane	plane;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (obj == NULL)
		return (1); // TODO: error message
	if (ft_tablen(tokens) != 4)
		return (1); // TODO: error message
	if (parse_vector(tokens[1], &plane.coords))
		return (1); // TODO: error message
	if (parse_vector(tokens[2], &plane.vect))
		return (1); // TODO: error message
	if (parse_color(tokens[3], &plane.color))
		return (1); // TODO: error message
	normalize(&plane.vect);
	obj->object.plane = plane;
	if (data->objects == NULL)
		data->objects = obj;
	else
	{
		obj->next = data->objects;
		data->objects = obj;
	}
	return (0);
}
