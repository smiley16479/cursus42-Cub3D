/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_shape_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:34:34 by adtheus           #+#    #+#             */
/*   Updated: 2020/01/12 00:47:56 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <mlx.h>
#include "essai.h"
#include "at_mlx_shape_line.h"


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

void draw_me_a_line(t_data data)
{
	int x;
	float a;
	float b;

	x = data.line_shape->origin_x;
	a = (float)(data.line_shape->fin_y - data.line_shape->origin_y)
		/ ((b = (float)(data.line_shape->fin_x - data.line_shape->origin_x)) == 0 ? 1 : b);
	b = data.line_shape->origin_y - a * data.line_shape->origin_x;
	printf("a: %f\n", a);
	while (x <= data.line_shape->fin_x)
	{
		my_mlx_pixel_put(data, x, a * x + b, data.line_shape->color);
		++x;
	}
}

int     render_next_frame(void *su)
{
    mlx_put_image_to_window(((t_data*)su)->mlx, ((t_data*)su)->mlx_win, ((t_data*)su)->img, 0, 0);
	return (0);
}
/*
int main()
{
	t_data  *su;
	t_line *line_shape;
	
	constructor_t_data(&su);
	constructor_t_line(&line_shape);
	*line_shape = initializer_t_line(100, 100, 110, 80, 0x0000FF00);
	*su = initializer_t_data(64 * 5, 64 * 5);//(64 * map_side, 64 * map_side); // 1920, 1080,
	su->line_shape = line_shape;
	su->img = mlx_new_image(su->mlx, su->window_width, su->window_heigth);
	su->addr = mlx_get_data_addr(su->img, &(su->bits_per_pixel), &(su->line_length),&(su->endian));
	draw_me_a_line(*su); // <-- marche
	mlx_put_image_to_window(su->mlx, su->mlx_win, su->img, 0, 0);
	// mlx_loop_hook(su->mlx, render_next_frame, (void*)su);
	mlx_loop(su->mlx);
	return (0);
}*/