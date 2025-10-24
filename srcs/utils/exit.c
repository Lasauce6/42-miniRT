# include "miniRT.h"

int message_error(char *format, char *detail, int exit_no)
{
	if (!detail)
		printf(format, STR_PROG_NAME);
	else
		printf(format, STR_PROG_NAME, detail);
	return (exit_no);
}

void	*free_light(t_light *light)
{

}

void	*error_null(char *format, char *detail)
{
	message_error(format, detail, EXIT_FAILURE);
	return (NULL);
}

int	*error_failure(char *format, char *detail)
{
	return (message_error(format, detail, EXIT_FAILURE));
}

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