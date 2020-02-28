/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:17:35 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/27 16:05:08 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include "map.h"
#include "at_mlx_hook.h"
#include "at_app_initializer.h"
#include "at_mlx_measure.h"
#include "at_mlx_player_handler.h"
#include "at_mlx_render.h"
#include "at_mlx_shape_square.h"
#include "at_mlx_shape_circle.h"
#include "at_mlx_shape_line.h"
#include "angle_convert.h"
#include "at_mlx_render.h"
// #include "at_mlx_measure copy.h"
//GLOBALE
	t_app  *g_su;


int main()
{
	t_player *pl;
	g_su = constructor_t_app();
	player_constructeur(&pl);
	*g_su = initializer_t_app(1000, 1000, "PinkY_WynKi");//(64 * map_side, 64 * map_side); // 1920, 1080,
	application_create_content();
	*pl = player_initializer(3, 3, 0);
	g_su->p = pl;

	for (int i = 0; i < MAP_SIDE; i++)
	{
		g_su->map[i] = map[i];
		// printf("cos 0 -> %d : %f\n", MAP_SIDE, pl->cst_tab[0][i]);
	}
	
	
	display_map(g_su->map);
	printf("player_orient : %.2f (ds le main l131)\n", ((t_player*)(g_su->p))->player_orient_origin);
	
	t_textur t_su;
    // char    *relative_path = "texture/brick.xpm";
    // char    *relative_path = "texture/GrayWalls.xpm";
    char    *relative_path = "texture/texture-floral-ornament-retro-elegant.xpm";
	t_su.text = mlx_xpm_file_to_image(g_su->mlx, relative_path, &(t_su.text_width), &(t_su.text_height));
	t_su.text_tab[0] = mlx_get_data_addr(t_su.text, &(t_su.text_bits_per_pixel), &(t_su.text_line_length),&(t_su.endian));
	t_su.addr = mlx_get_data_addr(t_su.text, &(t_su.text_bits_per_pixel), &(t_su.text_line_length),&(t_su.endian));
	g_su->t = &t_su;
	
	at_mlx_hook_loop(pl);	
	mlx_loop_hook(g_su->mlx, render_next_frame1, (void*)g_su);
	
	return (mlx_loop(g_su->mlx));
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
    t_app  *g_su;
	t_square *square_shape;
	t_circle *circle_shape;
	t_line *line_shape;
	
	constructor_t_app(&g_su);
	for (int i = 0; i < 5; i++)
		g_su->map[i] = map[i];
	constructor_t_square(&square_shape);
	constructor_t_circle(&circle_shape);
	constructor_t_line(&line_shape);
	
	
	// measure(g_su->map, player_pos(g_su->map));
	// player_init_pos(g_su);
	// printf("y : %.2f, x : %.2f\n",g_su->player_y, g_su->player_x);

	*square_shape = initializer_t_square(50, 50, 50, 0x0000FF00); //0x0000FF00);
	*line_shape = initializer_t_line(100, 100, 180, 200, 0x0000FF00);
	*g_su = initializer_t_app(64 * map_side, 64 * map_side);//(64 * map_side, 64 * map_side); // 1920, 1080,
	*circle_shape = initializer_t_circle(g_su->window_width / 2, g_su->window_heigth / 2, 10, 0x0000FF00); //0x0000FF00);
	g_su->color_offset = 0;
	g_su->square_shape = square_shape;
	g_su->line_shape = line_shape;
	g_su->shape = circle_shape;

    g_su->img = mlx_new_image(g_su->mlx, g_su->window_width, g_su->window_heigth);
    g_su->addr = mlx_get_app_addr(g_su->img, &(g_su->bits_per_pixel), &(g_su->line_length),
                                 &(g_su->endian));

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
				draw_me_a_square(*g_su);
			}
			++j; 
		}
		++i;
	}
 
	draw_me_a_circle(*g_su);  // <-- marche
	// draw_me_a_square(*g_su);  // <-- marche
	// draw_me_a_line(*g_su); // <-- marche
    // my_mlx_pixel_put(*g_su, x, y, 0x0000FF00);
    mlx_put_image_to_window(g_su->mlx, g_su->mlx_win, g_su->img, 0, 0);

	t_vars vars;
	vars.mlx = g_su->mlx;
	vars.mlx_win = g_su->mlx_win;

	//Voici les hook pour les interuptions de touches
	mlx_key_hook(vars.mlx_win, close_window, &vars);


	mlx_hook(vars.mlx_win, 2, 1L<<0, msg_keypressed_window, &vars);
	mlx_hook(vars.mlx_win, 3, 1L<<1, msg_keyreleased_window, &vars);
	mlx_hook(vars.mlx_win, 02, 1L, close_window, &vars);
	
	//voici le hook pour une animation
	mlx_loop_hook(g_su->mlx, render_next_frame, (void*)g_su);

	//voici le hook pour le programme
	mlx_loop(g_su->mlx);
	mlx_destroy_window(g_su->mlx, g_su->mlx_win);
	return (0);
}
*/
