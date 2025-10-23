#include "mlx_utils.h"
#include <stdio.h>

int init_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (printf("Error: mlx_init failed\n"), 1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		return (printf("Error: mlx_new_window failed\n"), 1);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);//create an image buffer
	if (!mlx->img.img)
		return (printf("Error: mlx_new_image failed\n"), 1);
	mlx->img.addr = mlx_get_date_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.line_length, &mlx->img.endian);//retrive the address of the pixel date
	if (!mlx->img.addr)
		return (printf("Erro: mlx_get_data_addr failed\n"), 1);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;//the adress of the pixel
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + y * img->line_length + x * (img->bpp / 8);//Pixel address = starting address + row offset + column offset
	*(unsigned int *)dst = color;
}

void	render_image(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

int	close_window(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destory_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
		free(mlx->mlx);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 53 || keycode == 65307) // ESC(macOS/Linux)
		close_window(mlx);
	return (0);
}