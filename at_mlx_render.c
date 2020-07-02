/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:09:04 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/02 12:01:08 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_mlx_render.h"

static inline void	clear_screen(void)
{
	const char	*clear_screen_ansi;

	clear_screen_ansi = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, clear_screen_ansi, 10);
}

void				display_terminal(void)
{
	char	*screen_str;
	int		h;
	int		y;
	int		x;
	double	x_rad_to_add;
	double	x_rad;

	x_rad_to_add = deg_to_rad(60. / g_su->size.x);
	x_rad = deg_to_rad(30);
	g_su->p->player_orient = g_su->p->player_orient_origin + x_rad;
	if (!(screen_str = malloc((g_su->size.x * g_su->size.y + 1))))
		return ;
	x = -1;
	while (++x < g_su->size.x)
	{
		x_rad -= x_rad_to_add;
		g_su->p->player_orient -= x_rad_to_add;
		h = g_su->e_dist / distance(g_su->p, x_rad);
		y = -1;
		while (++y < g_su->size.y)
			if (x == g_su->size.x - 1)
				screen_str[x + (g_su->size.x * y)] = '\n';
			else
			{
				if (y >= (g_su->size.y - h) / 2 && y < (g_su->size.y + h) / 2)
					screen_str[x + (g_su->size.x * y)] = '!' + g_su->p->w_o;
				else
					screen_str[x + (g_su->size.x * y)] = ' ';
			}
	}
	clear_screen();
	write(1, screen_str, g_su->size.x * g_su->size.y);
	free(screen_str);
}

/*
**	http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/...
**	...affichage/3d/raycasting/theorie/03-projection
**	Dimensions de l’écran de projection = 320 x 200 (à vous de le choisir)
**	Centre de l’écran de projection = (160,100)
**	Distance entre la camera et l’écran de projection = 277
**	Angle entre deux rayons consécutifs = 60/320 degrés
*/

void				display_wall(int x, double distance)
{
	int		height;
	int		y;
	int		color_tab[4] = {0x00FF0000, 0x0000FF00, 0x000000FF, 0x00f5f242};

	height = g_su->e_dist / distance;
	y = 0;
	while (y < g_su->size.y)
		if (y >= g_su->size.y / 2 - (height / 2) &&
			y < g_su->size.y / 2 + (height / 2))
			p_p(g_su->su_img, x, y++, color_tab[g_su->p->w_o]);
		else
			p_p(g_su->su_img, x, y++, 0x00000000);
}

/*
**	Trouve l’endroit ou le mur s’arrête
**	Trouve l’orientation du sol
**	Récupère la valeur du pixel touché
**	if (p->w_o == EST_bleu || p->w_o == OUEST_jaune)
**		px = (int)(p->wall_impact * g_su->t->t_h[1] +
**			(int)floor_offset * g_su->t->t_w[1]) * 4;
**	else
**		px = (int)(p->wall_impact * g_su->t->t_w[1] +
**		(int)floor_offset * g_su->t->t_h[1]) * 4;
**	p_p(g_su->su_img, x,  y,
**	*(int*)&(g_su->t->t_t[1][px % (g_su->t->t_w[1] * g_su->t->t_h[1])]));
**	floor_offset += g_su->t->t_h[1] / ((g_su->size.y - height) / 2 + height);
*/

/*
** 	double		h; //height
**	double 		o; //offset
**	int i = 4; // le numéro de la texture concernée :
**	à changer quand on gerera le dinamique
*/

void				display_sprite(int x, int y, t_player *p)
{
	double	h;
	double	o;
	int		px;
	int		i;

	i = 4;
	while (p->s_num >= 0)
	{
		h = g_su->e_dist / p->s_v2[p->s_num].s_d;
		(o = (h - g_su->size.y) / 2 * g_su->t->t_h
		[p->s_v2[p->s_num].sprite] / h) < 0 ? o = 0 : 0;
		y = -1;
		while (++y < g_su->size.y)
			if (0 <= p->s_v2[p->s_num].s_imp && p->s_v2[p->s_num].s_imp < 1)
				while ((g_su->size.y - h) / 2 <= y && y <= (g_su->size.y + h)
						/ 2 && y < g_su->size.y - 1)
				{
					px = (int)(p->s_v2[p->s_num].s_imp * g_su->t->t_w[i] +
					(int)o * g_su->t->t_w[i]) * 4;
					if (*(int*)&(g_su->t->t_t[i][px]) != 0)
						p_p(g_su->su_img, x, y, *(int*)&(g_su->t->t_t[i][px]));
					++y;
					o += g_su->t->t_h[i] / h;
				}
		--p->s_num;
	}
}

void				display_textured_wall(int x, double distance, t_player *p)
{
	double		h;
	double		of;
	int			y;
	int			px;

	h = g_su->e_dist / distance;
	(of = (h - g_su->size.y) / 2 * g_su->t->t_h[p->w_o] / h) < 0 ? of = 0 : 0;
	y = -1;
	while (++y < g_su->size.y)
		if ((g_su->size.y - h) / 2 <= y && y <= (g_su->size.y + h) / 2 - 1)
		{
			px = (int)(p->wall_impact * g_su->t->t_w[p->w_o] +
			(int)of * g_su->t->t_w[p->w_o]) * 4;
			p_p(g_su->su_img, x, y, *(int*)&(g_su->t->t_t[p->w_o][px]));
			of += g_su->t->t_h[p->w_o] / h;
		}
		else
			y < g_su->size.y / 2 ? p_p(g_su->su_img, x, y, g_su->t->fc.x) :
			p_p(g_su->su_img, x, y, g_su->t->fc.y);
	display_sprite(x, y, p);
}

int					render_next_frame(void)
{
	int		x;
	double	x_rad_to_add;
	double	x_rad;

	x = 0;
	x_rad_to_add = deg_to_rad(60. / g_su->size.x);
	x_rad = deg_to_rad(30);
	// *(g_su->su_img) = create_image(g_su->size.x, g_su->size.y);
	g_su->p->player_orient = g_su->p->player_orient_origin + x_rad;
	while (x < g_su->size.x)
	{
		x_rad -= x_rad_to_add;
		g_su->p->player_orient -= x_rad_to_add;
		// display_wall(x, distance(g_su->p) * cos(x_rad));
		display_textured_wall(x, distance(g_su->p, x_rad), g_su->p);
		++x;
	}
	// display_terminal();
	if (g_su->save && !(g_su->save = 0))
		bitmap();
	mlx_put_image_to_window(g_su->mlx, g_su->mlx_win,
							g_su->su_img->img_ptr, 0, 0);
	player_mov_hook(g_su->p);
	// mlx_destroy_image(g_su->mlx, g_su->su_img->img_ptr);
	return (0);
}
