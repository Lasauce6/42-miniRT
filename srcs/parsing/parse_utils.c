/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:30:54 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/09 17:18:31 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	parse_vector(char *str, t_vec *vec)
{
	int		i;
	char	**split;

	i = -1;
	split = ft_split(str, ',');
	if (split == NULL)
		return (1);
	while (split && split[++i])
		if (!ft_isfloat(split[i]))
			return (ft_free_split(split), 1);
	if (ft_tablen(split) != 3)
		return (ft_free_split(split), 1);
	else
	{
		vec->x = ft_atofloat(split[0]);
		vec->y = ft_atofloat(split[1]);
		vec->z = ft_atofloat(split[2]);
	}
	ft_free_split(split);
	return (0);
}

int	parse_color(char *str, int *color)
{
	int		i;
	char	**split;

	i = -1;
	split = ft_split(str, ',');
	while (split && split[++i])
		if (!is_(split[i]))
			return (ft_free_split(split), 1);
	if (ft_tablen(split) != 3)
		return (ft_free_split(split), 1);
	else
	{
		*color = get_color(atoi())
	}
	return (0);
}
