/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:47:32 by rbaticle          #+#    #+#             */
/*   Updated: 2025/11/07 13:30:19 by rbaticle         ###   ########.fr       */
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
	return (message_error(STR_ERR_INPUT, NULL, 1));
}

static int	check_line(char *line, t_data *data, int file)
{
	char	**tokens;

	if (!ft_strncmp(line, "#", 1))
		return (0);
	tokens = ft_split_max(line, " \t\n\v\f\r");
	if (tokens == NULL)
		return (1);
	if (ft_tablen(tokens) == 0)
		return (ft_free_split(tokens), 0);
	if (identify(tokens, data))
	{
		ft_free_split(tokens);
		while (line)
		{
			free(line);
			line = get_next_line(file);
		}
		close(file);
		free_table(data);
		exit(1);
	}
	ft_free_split(tokens);
	return (0);
}

int	is_invalid_file(t_data *data)
{
	if (data->ambient.id == null)
		return (message_error(STR_ERR_MISSING_ELE, NULL, 1));
	if (data->camera.id == null)
		return (message_error(STR_ERR_MISSING_ELE, NULL, 1));
	if (!data->light)
		return (message_error(STR_ERR_MISSING_ELE, NULL, 1));
	return (0);
}

static int	is_file_rt(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 3)
		return (1);
	if (filename[len - 3] == '.' && \
		filename[len - 2] == 'r' && \
		filename[len - 1] == 't')
		return (1);
	else
		return (0);
}

int	parse_file(char *filename, t_data *data)
{
	int		file;
	char	*line;

	if (!is_file_rt(filename))
		return (message_error(STR_USAGE, NULL, 1));
	file = open(filename, O_RDONLY);
	if (file == -1)
		return (message_error(STR_OPEN, filename, 1));
	line = get_next_line(file);
	if (line)
		check_line(line, data, file);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		if (line)
		{
			if (check_line(line, data, file))
				return (free(line), 1);
		}
	}
	close(file);
	return (is_invalid_file(data));
}
