/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:49:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/03 15:21:42 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	parse_ambiant_light(char **tokens, t_data *data)
{
	t_ambiant_light	l;
	char			**split;

	if (ft_tablen(tokens) != 3)
		return (1);
	if (!ft_strncmp(tokens[1], "0.", 2) || !ft_strncmp(tokens[1], "1.", 2)
		&& ft_strlen(tokens[1]) == 3)
	{
		split = ft_split(tokens[2], ',');
		if (split == NULL || ft_tablen(split) != 3)
			return (1);
		if (ft_atoi(split[0]) > 255 || ft_atoi(split[0]) < 0
			|| ft_atoi(split[1]) > 255 || ft_atoi(split[1]) < 0
			|| ft_atoi(split[2]) > 255 || ft_atoi(split[2]) < 0)
			return (free(split), 1);
		l.ratio = ft_atof(tokens[1]);
		l.color = get_color(ft_atoi(split[0]), ft_atoi(split[1]),
				ft_atoi(split[2]));
	}
	return (ft_free_split(split), 0);
}
