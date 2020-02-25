#include <stdio.h>
#include "at_mlx_pixel_put.h"

void	my_mlx_pixel_put(t_image img, int x, int y, int color)
{
    char    *dst;

	if (x < 0 || x >= img.size.x || y < 0 || y >= img.size.y)
	{
		printf("window's range overflow in: my_mlx_pixel_put()\n");
		return ;
	}
	dst = img.addr+ ((y * img.line_length + x * (img.bits_per_pixel / 8)));
	// printf("dst :%p\n", dst);
    *(unsigned int*)dst = (unsigned int)color;
}
