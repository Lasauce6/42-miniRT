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
	return (1);
	//return(error_failure(STR_ERR_PARSER_ELE, NULL));
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
	{
		ft_free_split(tokens);//WHY
		return(error_failure(STR_ERR_INPUT,NULL));
	}
		//return (free(tokens), 1);
	ft_free_split(tokens);
	return (0);
}

int	is_invalid_file(t_data *data)
{
	if (data->ambient.id == null)
		//return (1); // DONE: error message
		error_failure(STR_ERR_MISSING_ELE, NULL);
	if (data->camera.id == null)
		//return (1); // DONE: error message
		error_failure(STR_ERR_MISSING_ELE, NULL);
	if (!data->light)
		//return (1); // DONE: error message
		error_failure(STR_ERR_MISSING_ELE, NULL);
	return (0);
}

static int	is_file_rt(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	if (filename[len - 3] == '.' && \
		filename[len - 2] == 'r' && \
		filename[len - 1] == 't')
		return (1);
	else
		return(0);
}

int	parse_file(char *filename, t_data *data)
{
	int		file;
	char	*line;

	if (!is_file_rt(filename))
		error_failure(STR_USAGE, NULL);
	file = open(filename, O_RDONLY);
	if (file == -1)
		//return (1); // DONE: error message
		error_failure(STR_OPEN, filename);
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
	close(file);// ADD
	return (is_invalid_file(data));
}
