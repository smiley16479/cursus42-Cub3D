/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:09:04 by adtheus           #+#    #+#             */
/*   Updated: 2020/03/09 20:54:03 by adtheus          ###   ########.fr       */
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
	double 		offset;
	double		floor_offset;
	int			y;
	int			px;

	height = 277 / distance;
	// on calcule la proportion de la texture sur y a afficher en premier
	(offset = (height - g_su->size.y) / 2 * g_su->t->text_height[0] / height) < 0 ? offset = 0 : 0;

	// offset pour le Floor & Ceilling // On sait pas encore trop ce qu'on fait
	// if (p->wall_orient == EST_bleu || p->wall_orient == OUEST_jaune) // SUD_rouge == 0 , NORD_vert == 1
		floor_offset = g_su->size.y - height < 0 ? 0 : (g_su->size.y - height) / 2 + height;
	
	y = -1;
	while(++y < g_su->size.y)
	{
		if ((g_su->size.y - height) / 2 <= y && y <= (g_su->size.y + height) / 2 - 1)
		{
			if (p->sprite_num)
				while (p->sprite_num-- >= 0)
				{
					// int i = 0; // servira à itérer sur l'axe y en fonction du 
					// calcul de la distance qui est encore à faire pour dessiner successivement les sprites
					my_mlx_pixel_put(*(g_su->su_img), x, y, 0x00FF0000);

				}
			else
			{		
				px = (int)(p->wall_impact * g_su->t->text_width[0] + (int)offset * g_su->t->text_width[0]) * 4;
				my_mlx_pixel_put(*(g_su->su_img), x, y, *(int*)&(g_su->t->text_tab[0][px]));
				offset += g_su->t->text_height[0] / height;
			}
		}
		else
			/*
		{
Trouve l’endroit ou le mur s’arrête
Trouve l’orientation du sol
Récupère la valeur du pixel touché 
			if (p->wall_orient == EST_bleu || p->wall_orient == OUEST_jaune)
				px = (int)(p->wall_impact * g_su->t->text_height[1] + (int)floor_offset * g_su->t->text_width[1]) * 4;
			else
				px = (int)(p->wall_impact * g_su->t->text_width[1] + (int)floor_offset * g_su->t->text_height[1]) * 4;
			my_mlx_pixel_put(*(g_su->su_img), x,  y, 
			*(int*)&(g_su->t->text_tab[1][px % (g_su->t->text_width[1] * g_su->t->text_height[1])]));
			floor_offset += g_su->t->text_height[1] / ((g_su->size.y - height) / 2 + height);
		}
			*/
		// else
			my_mlx_pixel_put(*(g_su->su_img), x,  y, 0x00000000);
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
	double x_rad_to_add = deg_to_rad(60. / g_su->size.x);
	double x_rad = deg_to_rad(30);

	*(g_su->su_img) = create_image(g_su->size.x, g_su->size.y);
	g_su->p->player_orient = g_su->p->player_orient_origin + x_rad;
	while (x < g_su->size.x)
	{
		x_rad -= x_rad_to_add;
		g_su->p->player_orient -= x_rad_to_add;

		// display_wall(x, distance(g_su->p) * cos(x_rad)/*, g_su->p*/);
		display_textured_wall(x, distance(g_su->p, x_rad), g_su->p);
		// if (x==0)
			// printf(" g_su->p->sprite_v2[0] : (%f, %f)\n", g_su->p->sprite_v2[0].x,  g_su->p->sprite_v2[0].y);

		++x;
	}
    mlx_put_image_to_window(g_su->mlx, g_su->mlx_win, g_su->su_img->img_ptr, 0, 0);
	mlx_destroy_image(g_su->mlx, g_su->su_img->img_ptr);
	player_mov_hook(g_su->p);
	return (0);
}
