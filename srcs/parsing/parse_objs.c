/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:25:08 by rbaticle          #+#    #+#             */
/*   Updated: 2025/11/07 13:21:35 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	parse_sphere(char **tokens, t_data *data)
{
	t_sphere	s;
	t_obj		*obj;

	obj = create_object(data, sphere);
	if (obj == NULL)
		return (message_error(STR_ERR_MALLOC, NULL, 1));
	if (ft_tablen(tokens) != 4)
		return (message_error(STR_ERR_FILE_INFO, NULL, 1));
	if (parse_vector(tokens[1], &s.pos, VECTOR))
		return (message_error(STR_ERR_PARSER_VECTOR, tokens[1], 1));
	if (parse_double(tokens[2], &s.radius, SIZE))
		return (message_error(STR_ERR_PARSER_DOUBLE, tokens[2], 1));
	s.radius /= 2.0;
	if (parse_color(tokens[3], &s.color))
		return (message_error(STR_ERR_PARSER_COLOR, tokens[3], 1));
	obj->object.sphere = s;
	return (0);
}

int	parse_plane(char **tokens, t_data *data)
{
	t_plane	pl;
	t_obj	*obj;

	obj = create_object(data, plane);
	if (obj == NULL)
		return (message_error(STR_ERR_MALLOC, NULL, 1));
	if (ft_tablen(tokens) != 4)
		return (message_error(STR_ERR_FILE_INFO, NULL, 1));
	if (parse_vector(tokens[1], &pl.pos, VECTOR))
		return (message_error(STR_ERR_PARSER_VECTOR, tokens[1], 1));
	if (parse_vector(tokens[2], &pl.dir, NORMAL))
		return (message_error(STR_ERR_PARSER_VECTOR, tokens[2], 1));
	if (parse_color(tokens[3], &pl.color))
		return (message_error(STR_ERR_PARSER_COLOR, tokens[3], 1));
	obj->object.plane = pl;
	return (0);
}

int	parse_cylinder(char **tokens, t_data *data)
{
	t_cylinder	cyl;
	t_obj		*obj;

	obj = create_object(data, cylinder);
	if (obj == NULL)
		return (message_error(STR_ERR_MALLOC, NULL, 1));
	if (ft_tablen(tokens) != 6)
		return (message_error(STR_ERR_FILE_INFO, NULL, 1));
	if (parse_vector(tokens[1], &cyl.pos, VECTOR))
		return (message_error(STR_ERR_PARSER_VECTOR, tokens[1], 1));
	if (parse_vector(tokens[2], &cyl.dir, NORMAL))
		return (message_error(STR_ERR_PARSER_VECTOR, tokens[2], 1));
	cyl.dir = unitary_vector(&cyl.dir);
	if (parse_double(tokens[3], &cyl.radius, SIZE))
		return (message_error(STR_ERR_PARSER_DOUBLE, tokens[3], 1));
	cyl.radius /= 2.0;
	if (parse_double(tokens[4], &cyl.height, SIZE))
		return (message_error(STR_ERR_PARSER_DOUBLE, tokens[4], 1));
	if (parse_color(tokens[5], &cyl.color))
		return (message_error(STR_ERR_PARSER_COLOR, tokens[5], 1));
	obj->object.cylinder = cyl;
	return (0);
}
