/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:17:35 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/06 18:42:36 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include "essai.h"
#include "at_mlx_hook.h"
#include "at_mlx_measure.h"
#include "at_mlx_render.h"
#include "at_mlx_shape_square.h"
#include "at_mlx_shape_circle.h"
#include "at_mlx_shape_line.h"
#include "angle_convert.h"
// #include "at_mlx_measure copy.h"


void	my_mlx_pixel_put(t_data data, int x, int y, int color)
{
    char    *dst;

	if (x < 0 || x >= data.window_width || y < 0 || y >= data.window_heigth)
	{
		printf("window's range overflow in: my_mlx_pixel_put()\n");
		return ;
	}
	dst = data.addr + ((y * data.line_length + x * (data.bits_per_pixel / 8)));
    *(unsigned int*)dst = (unsigned int)color;
}

t_data	*constructor_t_data(t_data **img)
{
	*img = (t_data*)malloc(sizeof(t_data));
	if (*img == NULL)
		return (NULL);
	else
		return (*img);
}

t_data initializer_t_data(int window_width, int window_heigth)
{
	t_data to_return;
	to_return.window_width = window_width;
	to_return.window_heigth = window_heigth;
    if ((to_return.mlx = mlx_init()) == NULL)
		{
			to_return.str_error = "erreur ds initializer_t_data pour mlx_init()";
			return (to_return);
		}	
    if ((to_return.mlx_win = mlx_new_window(to_return.mlx, window_width, window_heigth, "Hello world!"))== NULL)
		{
			to_return.str_error = "erreur ds initializer_t_data pour mlx_new_window()";
			return (to_return);
		}
		return (to_return);
}

int who_wants_a_rainbow(t_data *su)
{
	// distance /= (708 / 100);
	// printf("ditance : %d et en fl %f, et color avant : %d\n", (int)distance, distance, get_g(*color));
	int *color = &(su->square_shape->color);
	int *i = &(su->color_offset);
	if (*i == 320)
		*i = 0;  
	((char*)color)[u_r] = (char)(sin(0.01 * *i + 0) * 127 + 128);
	((char*)color)[u_g] = (char)(sin(0.01 * *i + 2) * 127 + 128);
	((char*)color)[u_b] = (char)(sin(0.01 * *i + 4) * 127 + 128);

	// printf("color apres ; %d\n", *color);
	return (*color);
}


/*
int main()
{

	// double db = 0.5;
	// add_shade(db, 4294967295);
	// invert_color(4042322160);

	// int map[400] = {
		// 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,'W',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		// 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
	// };

	char map[5][5] = {
	{'1', '1', '1', '1', '1'}, 
	{'1', '0', '0', '0', '1'}, 
	{'1', '0', '0', '0', '1'}, 
	{'1', '0', '0', '0', '1'}, 
	{'1', '1', '1', '1', '1'}
};

	int map_side = 5;
    t_data  *su;
	t_square *square_shape;
	t_circle *circle_shape;
	t_line *line_shape;
	
	constructor_t_data(&su);
	for (int i = 0; i < 5; i++)
		su->map[i] = map[i];
	constructor_t_square(&square_shape);
	constructor_t_circle(&circle_shape);
	constructor_t_line(&line_shape);
	
	
	// measure(su->map, player_pos(su->map));
	// player_init_pos(su);
	// printf("y : %.2f, x : %.2f\n",su->player_y, su->player_x);

	*square_shape = initializer_t_square(50, 50, 50, 0x0000FF00); //0x0000FF00);
	*line_shape = initializer_t_line(100, 100, 180, 200, 0x0000FF00);
	*su = initializer_t_data(64 * map_side, 64 * map_side);//(64 * map_side, 64 * map_side); // 1920, 1080,
	*circle_shape = initializer_t_circle(su->window_width / 2, su->window_heigth / 2, 10, 0x0000FF00); //0x0000FF00);
	su->color_offset = 0;
	su->square_shape = square_shape;
	su->line_shape = line_shape;
	su->shape = circle_shape;

    su->img = mlx_new_image(su->mlx, su->window_width, su->window_heigth);
    su->addr = mlx_get_data_addr(su->img, &(su->bits_per_pixel), &(su->line_length),
                                 &(su->endian));

	int i, j;
	i = 0;
	while (i < map_side)
	{
		j = 0;
		while (j < map_side)
		{
			if (map[i][j] == '1')
			{
				*square_shape = initializer_t_square(64 * j, 64 * i, 64, 0x0000FF00); //0x0000FF00);
				draw_me_a_square(*su);
			}
			++j; 
		}
		++i;
	}
 
	draw_me_a_circle(*su);  // <-- marche
	// draw_me_a_square(*su);  // <-- marche
	// draw_me_a_line(*su); // <-- marche
    // my_mlx_pixel_put(*su, x, y, 0x0000FF00);
    mlx_put_image_to_window(su->mlx, su->mlx_win, su->img, 0, 0);

	t_vars vars;
	vars.mlx = su->mlx;
	vars.mlx_win = su->mlx_win;

	//Voici les hook pour les interuptions de touches
	mlx_key_hook(vars.mlx_win, close_window, &vars);


	mlx_hook(vars.mlx_win, 2, 1L<<0, msg_keypressed_window, &vars);
	mlx_hook(vars.mlx_win, 3, 1L<<1, msg_keyreleased_window, &vars);
	mlx_hook(vars.mlx_win, 02, 1L, close_window, &vars);
	
	//voici le hook pour une animation
	mlx_loop_hook(su->mlx, render_next_frame, (void*)su);

	//voici le hook pour le programme
	mlx_loop(su->mlx);
	mlx_destroy_window(su->mlx, su->mlx_win);
	return (0);
}
*/