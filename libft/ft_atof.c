/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:33:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/03 14:56:31 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_decimal(double res, char *str)
{
	size_t	i;
	double	dec;

	i = 0;
	dec = 0.1;
	while (ft_isdigit(str[i]))
	{
		res = res + (str[i++] - '0') * dec;
		dec = dec / 10;
	}
	return (res);
}

double	ft_atof(char *str)
{
	size_t	i;
	double	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		res = (res * 10) + str[i++] - '0';
	if (str[i] == '.')
		i++;
	return (get_decimal(res, &str[i]) * sign);
}
