/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:17:35 by adtheus           #+#    #+#             */
/*   Updated: 2020/01/04 18:37:17 by adtheus          ###   ########.fr       */
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
#include "at_mlx_square.h"

int		get_t(int trgb)
{
	// return (trgb & 0xFF000000);
	return (0xFF & ((char*)(&trgb))[3]);
}

int		get_r(int trgb)
{
	// return (trgb & 0xFF0000);
	return (0xFF & ((char*)(&trgb))[2]);
}

int		get_g(int trgb)
{
	// return (trgb & 0xFF00);
	return (0xFF & ((char*)(&trgb))[1]);
}

int		get_b(int trgb)
{
	// return (trgb & 0xFF);
	return (0xFF & *((char*)(&trgb)));
}

int get_oposite(int color)
{
	int opposite_color;
	opposite_color = 0;

	return (opposite_color);
}

void print_bin(char nb)
{
	printf("nb : %d\n", (int)nb);
	unsigned int i = 2147483648; // 128; //
	int ecart = 0;
	while (i > 0)
	{
		nb & i ? write(1, "1", 1) : write(1, "0", 1);
	 	!(++ecart % 4) && ecart != 32 ? write(1, " ", 1): 0;
		i /= 2;
	}
	write(1, "\n", 1);
}

int add_shade(double distance, unsigned int color)
{
	int color_shade;

	color_shade = 255;
	color_shade *= distance;
	color &= 0xFFFFFF00;
	color += color_shade;
	print_bin(color);
	return (color);
}

int invert_color(int color)
{
	int t;
	t = color & 0x000000FF;
	color = ~color;
	color &= 0xFFFFFF00;
	color += t;
	return (color);
}

void	my_mlx_pixel_put(t_data data, int x, int y, int color)
{
    char    *dst;

	if (x < 0 || x >= data.window_width || y < 0 || y >= data.window_heigth)
	{
		printf("sortie du window's range dans ton my_mlx_pixel_put\n");
		return ;
	}
    	{
			dst = data.addr + ((y * data.line_length + x * (data.bits_per_pixel / 8)));
    		*(unsigned int*)dst = (unsigned int)color;
		}
}

t_data	*constructor_t_data(t_data **img)
{
	*img = (t_data*)malloc(sizeof(t_data));
	if (*img == NULL)
		return (NULL);
	else
		return (*img);
}

t_line	*constructor_t_line(t_line **struc_line)
{
	*struc_line = (t_line*)malloc(sizeof(t_line));
	if (*struc_line == NULL)
		return (NULL);
	else
		return (*struc_line);
}

t_line initializer_t_line(int origin_x,int origin_y, int fin_x,int fin_y,int color)
{
	t_line to_return;
	to_return.origin_x = origin_x;
	to_return.origin_y = origin_y;
	to_return.fin_x = fin_x;
	to_return.fin_y = fin_y;
	to_return.color = color;
		return (to_return);
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

void draw_me_a_line(t_data data)
{
	int x;
	float a;
	float b;

	x = data.line_shape->origin_x;
	a = (float)(data.line_shape->fin_y - data.line_shape->origin_y)
		/ (float)(data.line_shape->fin_x - data.line_shape->origin_x);
	b = data.line_shape->origin_y - a * data.line_shape->origin_x;
	printf("a: %f\n", a);
	while (x <= data.line_shape->fin_x)
	{
		my_mlx_pixel_put(data, x, a * x + b, data.line_shape->color);
		++x;
	}
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

void draw_me_a_circle(t_data data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	/*
	while (++i < data.shape_struc->cote)
	{
		while (++j < data.shape_struc->cote)
		{
			my_mlx_pixel_put(data, i + data.shape_struc->origin_x, 
							j + data.shape_struc->origin_y, data.shape_struc->color);
		}
		j = 0;
	}*/
}

int main()
{

	// double db = 0.5;
	// add_shade(db, 4294967295);
	// invert_color(4042322160);

	int map[400] = {
		1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,'W',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
	};


    t_data  *su;
	t_square *square_shape;
	t_line *line_shape;
	
	constructor_t_data(&su);
	su->map = map;
	constructor_t_square(&square_shape);
	constructor_t_line(&line_shape);
	
	
	// measure(su->map, player_pos(su->map));
	player_init_pos(su);
	printf("y : %.2f, x : %.2f\n",su->player_y, su->player_x);

	*square_shape = initializer_t_square(50, 50, 50, 0x0000FF00); //0x0000FF00);
	*line_shape = initializer_t_line(100, 100, 180, 200, 0x0000FF00);
	*su = initializer_t_data(200, 200); // 1920, 1080,
	su->color_offset = 0;
	su->square_shape = square_shape;
	su->line_shape = line_shape;

    su->img = mlx_new_image(su->mlx, su->window_width, su->window_heigth);
    su->addr = mlx_get_data_addr(su->img, &(su->bits_per_pixel), &(su->line_length),
                                 &(su->endian));
	unsigned int a = 4278190290;
	print_bin((char)a);
	// draw_me_a_square(*su);  // <-- marche
	// draw_me_a_line(*su); // <-- marche
    // my_mlx_pixel_put(*su, x, y, 0x0000FF00);
    mlx_put_image_to_window(su->mlx, su->mlx_win, su->img, 0, 0);

	t_vars vars;
	vars.mlx = su->mlx;
	vars.mlx_win = su->mlx_win;

	//Voici les hook pour les interuptions de touches
	// mlx_key_hook(vars.mlx_win, close_window, &vars);

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