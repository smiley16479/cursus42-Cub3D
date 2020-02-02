
#include <mlx.h>

typedef struct  s_data {
	void    	*mlx;
	void    	*mlx_win;
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int     	img_width;
    int     	img_height;
    int     	win_width;
    int     	win_height;
}               t_data;


void	my_mlx_pixel_put(t_data data, int x, int y, int color)
{
    char    *dst;

	if (x < 0 || x >= data.win_width || y < 0 || y >= data.win_height)
	{
		printf("window's range overflow in: my_mlx_pixel_put()\n");
		return ;
	}
	dst = data.addr + ((y * data.line_length + x * (data.bits_per_pixel / 8)));
    *(unsigned int*)dst = (unsigned int)color;
}

int main()
{
	t_data su;
    char    *relative_path = "texture/texture-floral-ornament-retro-elegant.xpm";

    su.mlx = mlx_init();
	su.mlx_win = mlx_new_window(su.mlx, 500, 1000, "Hello world!");
    su.img = mlx_xpm_file_to_image(su.mlx, relative_path, &(su.img_width), &(su.img_height));
	su.addr = mlx_get_data_addr(su.img, &(su.bits_per_pixel), &(su.line_length),
		&(su.endian));
	mlx_put_image_to_window(su.mlx, su.mlx_win, su.img, 0, 0);
	mlx_loop(su.mlx);

	return (0);
}