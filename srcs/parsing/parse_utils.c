/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:30:54 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/07 16:02:16 by rbaticle         ###   ########.fr       */
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

int	parse_color(char *str, t_rgb *color)
{
	int		i;
	char	**split;

	i = -1;
	split = ft_split(str, ',');
	if (split == NULL)
		return (1);
	while (split && split[++i])
		if (!is_ulong(split[i]))
			return (ft_free_split(split), 1);
	if (ft_tablen(split) != 3)
		return (ft_free_split(split), 1);
	else if (ft_atoi(split[0]) > 255 || ft_atoi(split[0]) < 0
		|| ft_atoi(split[1]) > 255 || ft_atoi(split[1]) < 0
		|| ft_atoi(split[2]) > 255 || ft_atoi(split[2]) < 0)
		return (ft_free_split(split), 1);
	else
		*color = get_color(atoi(split[0]), atoi(split[1]), atoi(split[2]));
	ft_free_split(split);
	return (0);
}

int	parse_float(char *str, float *fl)
{
	if (!is_float(str))
		return (1);
	*fl = ft_atofloat(str);
	return (0);
}

int	parse_ulong(char *str, size_t *n)
{
	if (!is_ulong(str))
		return (1);
	*n = (size_t) ft_atoi(str);
	return (0);
}
