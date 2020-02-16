/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_shape_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:34:34 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/10 21:22:47 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <mlx.h>
 
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

void draw_me_a_line(t_app data)
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

int     render_next_frame(void *g_su)
{
    mlx_put_image_to_window(((t_app*)g_su)->mlx, ((t_app*)g_su)->mlx_win, ((t_app*)g_su)->img, 0, 0);
	return (0);
}
/*
int main()
{
	t_app  *g_su;
	t_line *line_shape;
	
	constructor_t_app(&g_su);
	constructor_t_line(&line_shape);
	*line_shape = initializer_t_line(100, 100, 110, 80, 0x0000FF00);
	*g_su = initializer_t_app(64 * 5, 64 * 5);//(64 * map_side, 64 * map_side); // 1920, 1080,
	g_su->line_shape = line_shape;
	g_su->img = mlx_new_image(g_su->mlx, g_su->window_width, g_su->window_heigth);
	g_su->addr = mlx_get_app_addr(g_su->img, &(g_su->bits_per_pixel), &(g_su->line_length),&(g_su->endian));
	draw_me_a_line(*g_su); // <-- marche
	mlx_put_image_to_window(g_su->mlx, g_su->mlx_win, g_su->img, 0, 0);
	// mlx_loop_hook(g_su->mlx, render_next_frame, (void*)g_su);
	mlx_loop(g_su->mlx);
	return (0);
}*/