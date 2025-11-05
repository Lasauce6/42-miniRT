/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:30:54 by rbaticle          #+#    #+#             */
/*   Updated: 2025/11/05 11:40:06 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	verify_type(void *val, t_type type)
{
	t_vec	vec;

	if (type == RATIO && ((*((double *) val) < 0.0)
			|| *((double *) val) > 1.0))
		return (1);
	if (type == NORMAL)
	{
		vec = *((t_vec *) val);
		if (vec.x < -1.0 || vec.x > 1.0 || vec.y < -1.0 || vec.y > 1.0
			|| vec.z < -1.0 || vec.z > 1.0)
			return (1);
	}
	if (type == FOV && *((size_t *) val) > 180)
		return (1);
	if (type == SIZE && (*(double *) val) < 0)
		return (1);
	return (0);
}

int	parse_vector(char *str, t_vec *vec, t_type type)
{
	int		i;
	char	**split;

	i = -1;
	split = ft_split(str, ',');
	if (split == NULL)
		return (1);
	while (split && split[++i])
		if (!is_double(split[i]))
			return (ft_free_split(split), 1);
	if (ft_tablen(split) != 3)
		return (ft_free_split(split), 1);
	else
	{
		vec->x = ft_atod(split[0]);
		vec->y = ft_atod(split[1]);
		vec->z = ft_atod(split[2]);
	}
	ft_free_split(split);
	return (verify_type(vec, type));
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

int	parse_double(char *str, double *d, t_type type)
{
	if (!is_double(str))
		return (1);
	*d = ft_atod(str);
	return (verify_type(d, type));
}

int	parse_ulong(char *str, size_t *n, t_type type)
{
	if (!is_ulong(str))
		return (1);
	*n = (size_t) ft_atoi(str);
	return (verify_type(n, type));
}
