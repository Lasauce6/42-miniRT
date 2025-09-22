/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:47:32 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/19 18:44:33 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	identify(char **tokens, t_data *data)
{
	if (!ft_strcmp(tokens[0], "A"))
		return (parse_ambient_light(tokens, data));
	if (!ft_strcmp(tokens[0], "C"))
		return (parse_camera(tokens, data));
	if (!ft_strcmp(tokens[0], "L"))
		return (parse_light(tokens, data));
	if (!ft_strcmp(tokens[0], "sp"))
		return (parse_sphere(tokens, data));
	if (!ft_strcmp(tokens[0], "pl"))
		return (parse_plane(tokens, data));
	if (!ft_strcmp(tokens[0], "cy"))
		return (parse_cylinder(tokens, data));
	return (1); // TODO: add error message
}

static int	check_line(char *line, t_data *data)
{
	char	**tokens;

	if (!ft_strncmp(line, "#", 1))
		return (0);
	tokens = ft_split_max(line, " \t\n\v\f\r");
	if (tokens == NULL)
		return (1);
	if (ft_tablen(tokens) == 0)
		return (0);
	if (identify(tokens, data))
		return (free(tokens), 1);
	ft_free_split(tokens);
	return (0);
}

int	is_invalid_file(t_data *data)
{
	if (data->ambient.id == null)
		return (1); // TODO: error message
	if (data->camera.id == null)
		return (1); // TODO: error message
	if (!data->light)
		return (1); // TODO: error message
	return (0);
}

int	parse_file(char *filename, t_data *data)
{
	int		file;
	char	*line;

	file = open(filename, O_RDONLY);
	if (file == -1)
		return (1); // TODO: error message
	line = get_next_line(file);
	if (line)
		check_line(line, data);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		if (line)
		{
			if (check_line(line, data))
				return (free(line), 1);
		}
	}
	return (is_invalid_file(data));
}
