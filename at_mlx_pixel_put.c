#include <stdio.h>
#include "at_mlx_pixel_put.h"

void	p_p(t_image *img, int x, int y, int color)
{
    char    *dst;

	if (x < 0 || x >= img->size.x || y < 0 || y >= img->size.y)
	{
		printf("window's range overflow in: p_p(%d; %d)\n", x,y);
		return ;
	}
	dst = img->addr + y * img->line_length + x * 4;
	// printf("dst :%p\n", dst);
    *(unsigned int*)dst = (unsigned int)color;
}
