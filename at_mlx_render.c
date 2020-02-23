/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:09:04 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/24 00:07:16 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_mlx_render.h"

void display_wall(int x, double distance)
{
	int		height;
	int		y;
	int		color_tab[4] = {0x00FF0000, 0x0000FF00, 0x000000FF, 0x00f5f242};
	t_image	img;
	
	img = *(g_su->su_img);
	height = 277 / distance;
	// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/03-projection
	// Dimensions de l’écran de projection = 320 x 200 (à vous de le choisir)
	// Centre de l’écran de projection = (160,100)
	// Distance entre la camera et l’écran de projection = 277
	// Angle entre deux rayons consécutifs = 60/320 degrés
	y  = 0;
	while(y < g_su->size.y)
		if (y >= g_su->size.y / 2 - (height / 2) && y < g_su->size.y / 2 + (height / 2))
			my_mlx_pixel_put(img, x,  y++, color_tab[g_su->p->wall_orient]);
		else
			my_mlx_pixel_put(img, x,  y++, 0x00000000);
}

void display_textured_wall(int x, double distance, t_player *p)
{
	int		height;
	int		y;
	int		step;
	int		px;
	int a = 0;

	height = 277 / distance > g_su->size.y ? g_su->size.y : 277 / distance;
	step = g_su->t->text_height / height;
	y  = 0;
	while(y < g_su->size.y)
	{
		if (y >= g_su->size.y / 2 - (height / 2) && y < g_su->size.y / 2 + (height / 2))
		{
			px = (a * g_su->t->text_width + (int)(p->wall_impact * g_su->t->text_width)) * 4;
			my_mlx_pixel_put(*(g_su->su_img), x, y, *(int*)&(g_su->t->text_tab[0][px]));
			a += step;
			++y;
		}
		else 
			my_mlx_pixel_put(*(g_su->su_img), x,  y++, 0x00000000);
	}
}

int     render_next_frame(t_app *g_su)
{
	int color = g_su->square_shape->color;
	//g_su->color_offset += 1;
	// who_wants_a_rainbow((t_app*)(g_su));
	draw_me_a_square();
    mlx_put_image_to_window(g_su->mlx, g_su->mlx_win, g_su->su_img->img_ptr, 0, 0);
	return (0);
}

int     render_next_frame1(void)
{
	int x = 0;
	double x_rad_to_add = deg_to_rad((double)60 / g_su->size.x);
	double x_rad = deg_to_rad(30);

	// *(g_su->su_img) = create_image(1000, 500);
	g_su->p->player_orient = g_su->p->player_orient_origin + x_rad;
	while (x < g_su->size.x)
	{
		x_rad -= x_rad_to_add;
		g_su->p->player_orient -= x_rad_to_add;

		// display_wall(x, d_incorrecte * cos(x_rad));
		display_textured_wall(x, d_incorrecte(g_su->p) * cos(x_rad), g_su->p);
		if (x==0)
		printf("pl->wall_impact (horizontal) : %f\n" /*player->orient : %f\n*/, g_su->p->wall_impact/*, rad_to_deg(g_su->p->player_orient_origin)*/);
		++x;
	}
    mlx_put_image_to_window(g_su->mlx, g_su->mlx_win, g_su->su_img->img_ptr, 0, 0);

    
	// mlx_destroy_image(g_su->mlx, g_su->su_img->img_ptr);
	return (0);
}