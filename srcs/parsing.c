/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:47:32 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/01 09:47:41 by rbaticle         ###   ########.fr       */
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
		while (line[i] && ft_isspace(line[i]))
			i++;
		nb_words++;
		while (line[i] && !ft_isspace(line[i]))
			i++;
	}
	return (nb_words);
}

int	check_line(char *line, t_data *data)
{
	int	nb_words;

	(void) data;
	nb_words = get_nb_words(line);
	if (nb_words != 4 || nb_words != 3 || nb_words != 6)
		return (1);
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
