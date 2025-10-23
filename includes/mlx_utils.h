#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <stdlib.h>
# include <mlx.h>

# define WIDTH 800
# define HEIGHT 600

typedef struct s_img
{
	void	*img;// Pointer to the image object created by MiniLibX (with mlx_new_image).
	char *addr; // Starting address of the image data in memory (the pixel buffer)
	int bpp; //bit per pixel,Bits per pixel: number of bits used to represent a pixel. Usually it’s 32 bits
	int	line_length;//Length (in bytes) of one line of the image.
	int endian; // endianness ; litte-endian endien = 0; big-endian endian = 1;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
} t_mlx;

#endif
