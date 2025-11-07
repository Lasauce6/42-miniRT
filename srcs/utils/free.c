/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jili <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:16:53 by jili              #+#    #+#             */
/*   Updated: 2025/11/07 15:17:04 by jili             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	free_lights(t_light **lights)
{
	t_light	*tmp;
	t_light	*l;

	l = *lights;
	while (l)
	{
		tmp = l;
		l = l->next;
		free(tmp);
	}
	*lights = 0;
}

void	*free_table(t_data *data)
{
	if (!data)
		return (NULL);
	if (data->light)
		free_lights(&(data->light));
	if (data->objs)
		free_objects(&(data->objs));
	return (NULL);
}
