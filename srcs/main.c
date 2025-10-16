/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:57:46 by rbaticle          #+#    #+#             */
/*   Updated: 2025/10/16 16:07:37 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && y < HEIGHT && x < WIDTH)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

t_data	init_data(void)
{
	t_data	data;

	data.img = NULL;
	data.addr = NULL;
	data.bits_per_pixel = 0;
	data.line_length = 0;
	data.endian = 0;
	data.mlx_ptr = NULL;
	data.win = NULL;
	data.camera.id = null;
	data.ambient.id = null;
	data.light = NULL;
	data.objs = NULL;
	data.winsize = HEIGHT * WIDTH;
	data.aspect_ratio = (double) WIDTH / (double) HEIGHT;
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = init_data();
	if (argc != 2)
		return (write(1, "ERROR", 5), 1);
	if (parse_file(argv[1], &data))
		return (write(1, "ERROR", 5), 1);
	data.mlx_ptr = mlx_init();
	data.win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "MiniRT");
	data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	cast_rays(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win, data.img, 0, 0);
	mlx_loop(data.mlx_ptr); // TODO: close with cross and escape and free all heap
}
