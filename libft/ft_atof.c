/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:33:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/08 12:14:05 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	size_t	i;
	double	res;
	double	sign;
	double	dec;

	i = 0;
	dec = 0.1;
	res = ft_atoi(str);
	if (res > 0)
		sign = 1.0;
	else
		sign = -1.0;
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res + (str[i++] - '0') * dec;
		dec = dec / 10;
	}
	return (res * sign);
}
