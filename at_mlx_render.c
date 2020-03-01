/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:09:04 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/28 19:07:54 by adtheus          ###   ########.fr       */
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
	double		height;
	double		step;
	double 		offset; // si tu l'as en double tu as la bonne taille mais un glitch
	// si tu le mets en int tu n'as pas toute le taille de la texture
	int			y;
	int			px;

	height = /*((277 / distance) > g_su->size.y) ? g_su->size.y :*/ 277 / distance;
	// printf("step : %f\n", step);
	y = 0;
	int draw_start = g_su->size.y / 2 - height / 2 < 0 ? 0 : g_su->size.y / 2 - height / 2;
	int draw_end = draw_start == 0 ? g_su->size.y : g_su->size.y / 2 + height / 2;
	step = (double)g_su->t->text_height / (1. * (draw_end - draw_start));//height; <--peut etre laisser height
	offset = draw_end - (draw_end - draw_start);//<-- ici que ça bug // (draw_start - g_su->size.y / 2 + height / 2) * step; //g_su->size.y / 2 - height / 2 < 0 ? (height / 2 - g_su->size.y / 2): 0; //
	while(y < g_su->size.y)
	{
		// if ((g_su->size.y / 2 - height / 2) <= y && y <= (g_su->size.y / 2 + height / 2))
		if (draw_start < y && y < draw_end - 1)
		{
			px = (int)(p->wall_impact * g_su->t->text_width + (int)offset * g_su->t->text_width) * 4.;
			// printf("px : %d\n", px);
			my_mlx_pixel_put(*(g_su->su_img), x, y, *(int*)&(g_su->t->text_tab[0][px]));
			offset += step;
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

	// *(g_su->su_img) = create_image(g_su->size.x, g_su->size.y);
	g_su->p->player_orient = g_su->p->player_orient_origin + x_rad;
	while (x < g_su->size.x)
	{
		x_rad -= x_rad_to_add;
		g_su->p->player_orient -= x_rad_to_add;

		// display_wall(x, d_incorrecte(g_su->p) * cos(x_rad)/*, g_su->p*/);
		display_textured_wall(x, d_incorrecte(g_su->p) * cos(x_rad), g_su->p);
		if (x==0)
			printf("player->orient : %f\n", rad_to_deg(g_su->p->player_orient_origin));
		++x;
	}
    mlx_put_image_to_window(g_su->mlx, g_su->mlx_win, g_su->su_img->img_ptr, 0, 0);
	// mlx_destroy_image(g_su->mlx, g_su->su_img->img_ptr);
	player_mov_hook(g_su->p);
	return (0);
}
