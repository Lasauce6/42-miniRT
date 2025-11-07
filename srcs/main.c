/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jili <jili@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:57:46 by rbaticle          #+#    #+#             */
/*   Updated: 2025/11/07 15:13:08 by jili             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && y < HEIGHT && x < WIDTH)
	{
		dst = data->addr + (y * data->line_length + \
				x * (data->bits_per_pixel / 8));
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
	data.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	return (data);
}

void	ft_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
		error_failure(STR_ERR_MLX, NULL, data);
	data->win = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "MiniRT");
	if (!(data->win))
		error_failure(STR_ERR_MLX, NULL, data);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!(data->img))
		error_failure(STR_ERR_MLX, NULL, data);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!(data->addr))
		error_failure(STR_ERR_MLX, NULL, data);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win, data->img, 0, 0);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = init_data();
	if (argc != 2)
		error_failure(STR_USAGE, NULL, &data);
	if (parse_file(argv[1], &data))
	{
		free_table(&data);
		exit(1);
	}
	ft_mlx(&data);
	return (0);
}
