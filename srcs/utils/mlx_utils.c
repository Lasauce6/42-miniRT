# include "miniRT.h"

int	close_window(t_data *data)
{
	if (data->img)
		mlx_destory_image(data->mlx_ptr, data->img);
    if (data->win)
		mlx_destory_window(data->mlx_ptr, data->win);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	exit(0);
	return (0);
}

