/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:25:08 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/19 14:42:07 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	parse_sphere(char **tokens, t_data *data)
{
	t_sphere	s;
	t_obj		*obj;

	obj = create_object(data, sphere);
	if (obj == NULL)
		return (1);
	if (ft_tablen(tokens) != 4)
		return (free(obj), 1); // TODO: error message
	if (parse_vector(tokens[1], &s.coords))
		return (free(obj), 1); // TODO: error message
	if (parse_float(tokens[2], &s.diam))
		return (free(obj), 1); // TODO: error message
	if (parse_color(tokens[3], &s.color))
		return (free(obj), 1); // TODO: error message
	obj->object.sphere = s;
	return (0);
}

int	parse_plane(char **tokens, t_data *data)
{
	t_plane	pl;
	t_obj	*obj;

	obj = create_object(data, plane);
	if (obj == NULL)
		return (1); // TODO: error message
	if (ft_tablen(tokens) != 4)
		return (free(obj), 1); // TODO: error message
	if (parse_vector(tokens[1], &pl.coords))
		return (free(obj), 1); // TODO: error message
	if (parse_vector(tokens[2], &pl.vect))
		return (1); // TODO: error message
	if (parse_color(tokens[3], &pl.color))
		return (free(obj), 1); // TODO: error message
	normalize(&pl.vect);
	obj->object.plane = pl;
	return (0);
}

int	parse_cylinder(char **tokens, t_data *data)
{
	t_cylinder	cyl;
	t_obj		*obj;

	obj = create_object(data, cylinder);
	if (obj == NULL)
		return (1); // TODO: error message
	if (ft_tablen(tokens) != 6)
		return (free(obj), 1); // TODO: error message
	if (parse_vector(tokens[1], &cyl.coords))
		return (free(obj), 1); // TODO: error message
	if (parse_vector(tokens[2], &cyl.axis))
		return (free(obj), 1); // TODO: error message
	normalize(&cyl.axis);
	if (parse_float(tokens[3], &cyl.diam))
		return (free(obj), 1); // TODO: error message
	if (parse_float(tokens[4], &cyl.height))
		return (free(obj), 1); // TODO: error message
	if (parse_color(tokens[5], &cyl.color))
		return (free(obj), 1); // TODO: error message
	obj->object.cylinder = cyl;
	return (0);
}
