/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:47:32 by rbaticle          #+#    #+#             */
/*   Updated: 2025/05/26 15:15:33 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	get_nb_words(char *line)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (line[i])
	{
		
	}
	return (nb_words);
}

int	check_line(char *line, t_data *data)
{
	int	nb_words;

	nb_words = get_nb_words(line);
	return (0);
}

int	parse_file(char *filename, t_data *data)
{
	int		file;
	char	*line;

	file = open(filename, O_RDONLY);
	if (file == -1)
		return (1);
	line = get_next_line(file);
	check_line(line, data);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		check_line(line, data);
	}
	return (0);
}
