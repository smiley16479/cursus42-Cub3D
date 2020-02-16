
#include <mlx.h>
#include "struc.h"
#include <stdio.h>

#define texture_side 32
/*
typedef struct  s_data {
	void    	*mlx;
	void    	*mlx_win;
    void        *img;
    void        *img_win;
    char        *img_addr;
    char        *img_win_addr;
    int         img_bits_per_pixel;
    int         img_line_length;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int     	img_width;
    int     	img_height;
    int     	win_width;
    int     	win_height;
}               t_app;

void	my_mlx_pixel_put(t_app data, int x, int y, int color)
{
    char    *dst;

	if (x < 0 || x >= data.win_width || y < 0 || y >= data.win_height)
	{
		printf("window's range overflow in: my_mlx_pixel_put(x = %d, y = %d)\n", x, y);
		return ;
	}
	dst = data.img_win_addr + ((y * data.line_length + x * (data.bits_per_pixel / 8)));
    *(unsigned int*)dst = (unsigned int)color;
}

void	my_mlx_pixel_put_handler(t_app data, int x, int y)
{
	while (y >= 0 && y < data.win_height)
	{
		while (x >= 0 && x < data.win_width)
		{
			my_mlx_pixel_put(data,  x, y, *((int*)(data.img_addr + (((y % texture_side) * data.img_line_length + (x % texture_side) * (data.img_bits_per_pixel / 8))))));
			++x;
		}
		x = 0;
		++y;
	}
}*/

t_textu_data init_texture(t_app g_su, char *relative_path)
{
	t_textu_data su_textur;

	su_textur.text = mlx_xpm_file_to_image(g_su.mlx, relative_path, &(su_textur.text_width), &(su_textur.text_height));
	su_textur.addr = mlx_get_app_addr(su_textur.text, &(su_textur.text_bits_per_pixel), &(su_textur.text_line_length),&(su_textur.endian));
	return (su_textur);
}
/*
int main()
{
	t_app g_su;
    char    *relative_path = "texture/brick.xpm";
	g_su.win_width = 160, g_su.win_height = 160;

    g_su.mlx = mlx_init();
	g_su.mlx_win = mlx_new_window(g_su.mlx, g_su.win_width, g_su.win_height, "Hello world!");

	g_su.img_win = mlx_new_image(g_su.mlx , g_su.win_width, g_su.win_height);
	g_su.img_win_addr = mlx_get_app_addr(g_su.img_win, &(g_su.bits_per_pixel), &(g_su.line_length),&(g_su.endian));

    g_su.img = mlx_xpm_file_to_image(g_su.mlx, relative_path, &(g_su.img_width), &(g_su.img_height));
	g_su.img_addr = mlx_get_app_addr(g_su.img, &(g_su.img_bits_per_pixel), &(g_su.img_line_length),&(g_su.endian));

	// my_mlx_pixel_put(g_su, x,  y, color);
	my_mlx_pixel_put_handler(g_su, 0, 0);

	mlx_put_image_to_window(g_su.mlx, g_su.mlx_win, g_su.img_win, 0, 0);
	mlx_loop(g_su.mlx);

	return (0);
}*/