/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:49:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/15 17:15:04 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	parse_ambient_light(char **tokens, t_data *data)
{
	t_ambient_light	l;

	if (ft_tablen(tokens) != 3)
		return (1); // TODO: error message
	if (data->ambient.id)
		return (1); // TODO: error message
	if (parse_color(tokens[2], &l.color))
		return (1); // TODO: error message
	if (parse_float(tokens[1], &l.ratio))
		return (1); // TODO: error message
	l.id = ambient_light;
	data->ambient = l;
	return (0);
}

int	parse_light(char **tokens, t_data *data)
{
	t_light	*l;

	l = malloc(sizeof(t_light));
	if (l == NULL)
		return (1); // TODO: error message
	l->next = NULL;
	if (ft_tablen(tokens) != 4)
		return (free(l), 1); // TODO: error message
	if (parse_vector(tokens[1], &l->coords))
		return (free(l), 1); // TODO: error message
	if (parse_float(tokens[2]), &l->ratio)
		return (free(l), 1); // TODO: error message
	if (parse_color(tokens[3]), &l->color)
		return (free(l), 1); // TODO: error message
	if (data->light == NULL)
		data->light = l;
	else
	{
		l->next = data->light;
		data->light = l;
	}
	return (0);
}
