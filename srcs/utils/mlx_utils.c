# include "miniRT.h"

int	close_window(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
    if (data->win)
		mlx_destroy_window(data->mlx_ptr, data->win);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_table(data);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	
	if (keycode == 53 || keycode == 65307) // ESC(macOS/Linux)
		close_window(data);
	return (0);
}
