/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:59:45 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/17 15:47:32 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	is_double(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '.')
			return (0);
	}
	return (1);
}

int	is_ulong(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

double	deg2rad(double deg)
{
	return (deg * (M_PI / 180.0));
}

double	rad2deg(double rad)
{
	return (rad * (180.0 / M_PI));
}

double	ft_atod(char *str)
{
	double	numb;
	double	flag;
	int		i;
	int		j;

	i = 0;
	j = 1;
	flag = 1;
	numb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			flag = -1.0;
	}
	while (str[i] >= 48 && str[i] <= 57)
		numb = (numb * 10 + (double)(str[i++] - 48));
	if (str[i] != '.')
		return (numb * flag);
	i++;
	while (str[i] >= 48 && str[i] <= 57 && j < 8)
		numb += (double)(str[i++] - 48) / pow(10, j++);
	return (numb * flag);
}
