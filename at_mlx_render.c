/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:09:04 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/06 18:56:16 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <math.h>
#include "essai.h"
#include "at_mlx_shape_square.h"
#include "at_mlx_measure.h"
#include "angle_convert.h"

int     render_next_frame(void *su)
{
	int color = ((t_data*)(su))->square_shape->color;
	((t_data*)(su))->color_offset += 1;
	// who_wants_a_rainbow((t_data*)(su));
	draw_me_a_square((*(t_data*)su));
    mlx_put_image_to_window(((t_data*)su)->mlx, ((t_data*)su)->mlx_win, ((t_data*)su)->img, 0, 0);
	return (0);
}

int     render_next_frame1(void *su)
{
	int x = 0;
	double x_rad_to_add = deg_to_rad((double)60 / ((t_data*)su)->window_width);
	double x_rad = deg_to_rad(30);
	double d_incorrecte;

	((t_data*)su)->player_orient = ((t_data*)su)->player_orient_origin + x_rad;
	while (x < ((t_data*)su)->window_width)
	{
		x_rad -= x_rad_to_add;
		((t_data*)su)->player_orient -= x_rad_to_add;
		d_incorrecte = distance_incorrecte(su);
		display_textured_wall(su, x, d_incorrecte * cos(x_rad));
		++x;
	}
    mlx_put_image_to_window(((t_data*)su)->mlx, ((t_data*)su)->mlx_win, ((t_data*)su)->img, 0, 0);
	return (0);
}