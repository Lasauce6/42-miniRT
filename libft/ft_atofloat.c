/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atofloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:14:22 by rbaticle          #+#    #+#             */
/*   Updated: 2025/09/08 12:15:05 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atofloat(char *str)
{
	size_t	i;
	float	res;
	float	sign;
	float	dec;

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
