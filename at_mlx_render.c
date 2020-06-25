/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:09:04 by adtheus           #+#    #+#             */
/*   Updated: 2020/03/13 10:43:55 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_mlx_render.h"

static inline void clearScreen(void)
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 10);
}

void display_terminal(void)
{
	char *screen_str;
	int		height;
	int		y;
	int		x;
	double x_rad_to_add = deg_to_rad(60. / g_su->size.x);
	double x_rad = deg_to_rad(30);
	g_su->p->player_orient = g_su->p->player_orient_origin + x_rad;
	if (!(screen_str = malloc((g_su->size.x * g_su->size.y + 1))))
		return;

	x = -1;
	while (++x < g_su->size.x)
	{
		x_rad -= x_rad_to_add;
		g_su->p->player_orient -= x_rad_to_add;
		height = g_su->e_dist / distance(g_su->p, x_rad);
		y = -1;
		while(++y < g_su->size.y)
			if (x == g_su->size.x - 1)
				screen_str[x + (g_su->size.x * y)] = '\n';
			else {
				if (y >= g_su->size.y / 2 - (height / 2) && y < g_su->size.y / 2 + (height / 2))
					screen_str[x + (g_su->size.x * y)] = '!' + g_su->p->wall_orient;
				else
					screen_str[x + (g_su->size.x * y)] = ' ';
			}
	}
	clearScreen();
	write(1, screen_str, g_su->size.x * g_su->size.y);
	free(screen_str);
}

void display_wall(int x, double distance)
{
	int		height;
	int		y;
	int		color_tab[4] = {0x00FF0000, 0x0000FF00, 0x000000FF, 0x00f5f242};

	height = g_su->e_dist / distance;
	// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/03-projection
	// Dimensions de l’écran de projection = 320 x 200 (à vous de le choisir)
	// Centre de l’écran de projection = (160,100)
	// Distance entre la camera et l’écran de projection = 277
	// Angle entre deux rayons consécutifs = 60/320 degrés
	y  = 0;
	while(y < g_su->size.y)
		if (y >= g_su->size.y / 2 - (height / 2) && y < g_su->size.y / 2 + (height / 2))
			my_mlx_pixel_put(g_su->su_img, x,  y++, color_tab[g_su->p->wall_orient]);
		else
			my_mlx_pixel_put(g_su->su_img, x,  y++, 0x00000000);
}

			/*
		{
Trouve l’endroit ou le mur s’arrête
Trouve l’orientation du sol
Récupère la valeur du pixel touché 
			if (p->wall_orient == EST_bleu || p->wall_orient == OUEST_jaune)
				px = (int)(p->wall_impact * g_su->t->text_height[1] + (int)floor_offset * g_su->t->text_width[1]) * 4;
			else
				px = (int)(p->wall_impact * g_su->t->text_width[1] + (int)floor_offset * g_su->t->text_height[1]) * 4;
			my_mlx_pixel_put(g_su->su_img, x,  y, 
			*(int*)&(g_su->t->text_tab[1][px % (g_su->t->text_width[1] * g_su->t->text_height[1])]));
			floor_offset += g_su->t->text_height[1] / ((g_su->size.y - height) / 2 + height);
		}
			*/

void display_sprite(int x, int y, t_player *p)
{
	double		s_height;
	double 		s_offset;
	int 		px;
	int i = 4; // le numéro de la texture concernée : à changer quand on gerera le dinamique

	while (p->s_num >= 0)
	{
		s_height = g_su->e_dist / p->sprite_v2[p->s_num].s_dist;
		(s_offset = (s_height - g_su->size.y) / 2 * g_su->t->text_height[p->sprite_v2[p->s_num].sprite] / s_height) < 0 ? s_offset = 0 : 0;
		y = -1;
		while (++y < g_su->size.y)
		{//Quand on mets plus d'un sprite sur la carte l'affichage freeze.
			if (0 <= p->sprite_v2[p->s_num].s_impact && p->sprite_v2[p->s_num].s_impact < 1)
				while  ((g_su->size.y - s_height) / 2 <= y && y <= (g_su->size.y + s_height) / 2 && y < g_su->size.y - 1)
				{
					px = (int)(p->sprite_v2[p->s_num].s_impact * g_su->t->text_width[i] + (int)s_offset * g_su->t->text_width[i]) * 4;
					if (*(int*)&(g_su->t->text_tab[i][px]) != 0)
						my_mlx_pixel_put(g_su->su_img, x, y, *(int*)&(g_su->t->text_tab[i][px]));
					y++;
					s_offset += g_su->t->text_height[i] / s_height;
				}
		}
		--p->s_num;
	}
}


void display_textured_wall(int x, double distance, t_player *p)
{
	double		height;
	double 		offset;
	double		s_height;
	double 		s_offset;
	// double		floor_offset;
	int			y;
	int			px;
	
	height = g_su->e_dist / distance;
	(offset = (height - g_su->size.y) / 2 * g_su->t->text_height[p->wall_orient] / height) < 0 ? offset = 0 : 0;
	y = -1;
	while(++y < g_su->size.y)
	{
		if ((g_su->size.y - height) / 2 <= y && y <= (g_su->size.y + height) / 2 - 1)
		{
			px = (int)(p->wall_impact * g_su->t->text_width[p->wall_orient] + (int)offset * g_su->t->text_width[p->wall_orient]) * 4;
			my_mlx_pixel_put(g_su->su_img, x, y, *(int*)&(g_su->t->text_tab[p->wall_orient][px]));
			offset += g_su->t->text_height[p->wall_orient] / height;
		}
		else
			y < g_su->size.y / 2 ? my_mlx_pixel_put(g_su->su_img, x,  y, g_su->t->fc.x) : my_mlx_pixel_put(g_su->su_img, x,  y, g_su->t->fc.y);
	}
	display_sprite(x, y, p);
}

int     render_next_frame1(void)
{
	int x = 0;
	double x_rad_to_add = deg_to_rad(60. / g_su->size.x);
	double x_rad = deg_to_rad(30);

	// *(g_su->su_img) = create_image(g_su->size.x, g_su->size.y);
	g_su->p->player_orient = g_su->p->player_orient_origin + x_rad;
	while (x < g_su->size.x)
	{
		x_rad -= x_rad_to_add;
		g_su->p->player_orient -= x_rad_to_add;

		// display_wall(x, distance(g_su->p) * cos(x_rad));
		display_textured_wall(x, distance(g_su->p, x_rad), g_su->p);
		// if (x==0)
			// printf(" g_su->p->sprite_v2[0] : (%f, %f)\n", g_su->p->sprite_v2[0].x,  g_su->p->sprite_v2[0].y);
		++x;
	}
	// display_terminal();
	if (g_su->save && !(g_su->save = 0))
		bitmap();
    mlx_put_image_to_window(g_su->mlx, g_su->mlx_win, g_su->su_img->img_ptr, 0, 0);
	player_mov_hook(g_su->p);
	// mlx_destroy_image(g_su->mlx, g_su->su_img->img_ptr);
	return (0);
}
