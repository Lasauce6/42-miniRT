/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:57:46 by rbaticle          #+#    #+#             */
/*   Updated: 2025/05/26 14:54:15 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("error");
	}
	parse_file(argv[1], &data);
	data.mlx_ptr = mlx_init();
	data.win = mlx_new_window(data.mlx_ptr, 1000, 800, "Hello world!");
	data.img = mlx_new_image(data.mlx_ptr, 1000, 800);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	my_mlx_pixel_put(&data, 5, 5, 0x00FFFFF);
	mlx_put_image_to_window(data.mlx_ptr, data.win, data.img, 0, 0);
	mlx_loop(data.mlx_ptr);
}
