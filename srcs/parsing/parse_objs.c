/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:25:08 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 19:57:59 by rbaticle         ###   ########.fr       */
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
	if (parse_vector(tokens[1], &s.pos))
		return (free(obj), 1); // TODO: error message
	if (parse_double(tokens[2], &s.radius))
		return (free(obj), 1); // TODO: error message
	s.radius /= 2.0;
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
	if (parse_vector(tokens[1], &pl.pos))
		return (free(obj), 1); // TODO: error message
	if (parse_vector(tokens[2], &pl.dir))
		return (1); // TODO: error message
	if (parse_color(tokens[3], &pl.color))
		return (free(obj), 1); // TODO: error message
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
	if (parse_vector(tokens[1], &cyl.pos))
		return (free(obj), 1); // TODO: error message
	if (parse_vector(tokens[2], &cyl.dir))
		return (free(obj), 1); // TODO: error message
	cyl.dir = unitary_vector(&cyl.dir);
	if (parse_double(tokens[3], &cyl.radius))
		return (free(obj), 1); // TODO: error message
	cyl.radius /= 2.0;
	if (parse_double(tokens[4], &cyl.height))
		return (free(obj), 1); // TODO: error message
	if (parse_color(tokens[5], &cyl.color))
		return (free(obj), 1); // TODO: error message
	obj->object.cylinder = cyl;
	return (0);
}
