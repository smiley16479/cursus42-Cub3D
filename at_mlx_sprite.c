/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:07:17 by adtheus           #+#    #+#             */
/*   Updated: 2020/03/13 08:23:31 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "at_mlx_sprite.h"
#include "struc.h"

void sprite_process(int x, int ajusteur, double y, double *tab)
{ //pale copie de l'ebauche faite ds measure.c a adapter/ameliorer
	int		is_sprite = 0;
	int		i;
		if ((is_sprite = which_sprite(g_su->map[(int)y][x + ajusteur])) && i < 100)
		{
			double dist_x, dist_y, delta_ang, delta_sprite_center;
			// dist_x = fabs(pl->player_x - (x + (tab[e_cos] < 0 ? -.5 : .5)));
			// dist_y = fabs(pl->player_y - ((int)y + (tab[e_sin] < 0 ? -.5 : .5)));
			dist_x = fabs(x + ajusteur + .5 - g_su->p->player_x); //tab[e_cos] > 0 ? x + ajusteur + .5 - pl->player_x : pl->player_x - (x + ajusteur) - .5; 
			dist_y = fabs(g_su->p->player_y - (int)y - .5); //tab[e_sin] > 0 ? pl->player_y - (int)y - .5 : (int)y - pl->player_y + .5;
			delta_ang = /*fabs(*/atan2(dist_x, dist_y) - g_su->p->player_orient/*)*/;
			g_su->p->sprite_v2[i].s_dist = hypot(dist_x, dist_y); //fabs((pl->player_x - x + tab[e_cos] < 0 ? -.5 : .5) / tab[e_cos]) * cos(tab[e_x_rad]);
			delta_sprite_center = g_su->p->sprite_v2[i].s_dist * tan(delta_ang); // ecart entre le centre du sprite et le point d'impact du rayon
			g_su->p->sprite_v2[i].s_dist = g_su->p->sprite_v2[i].s_dist * cos(delta_ang); // pour eviter le fishEye -> distance entre le rayon et le sprite
			g_su->p->sprite_v2[i].s_impact = delta_sprite_center; // g_su->p->wall_orient == EST_bleu ? y - (int)y : 1. - (y - (int)y);
			g_su->p->sprite_v2[i].sprite = is_sprite;
			if (-0.01 <= tab[e_x_rad] && tab[e_x_rad] <= 0.01)
				// printf("orient : %f, x_rad : %f, dist_x : %f, dist_y : %f, g_su->p->sprite_v2[i].s_dist(hypot) : %f, is_sprite %d;%d player (%.1f;%.1f)\n" ,rad_to_deg(g_su->p->player_orient_origin), tab[e_x_rad] ,dist_x, dist_y, g_su->p->sprite_v2[i].s_dist, /*is_sprite*/x + ajusteur , (int)(y), g_su->p->player_x, g_su->p->player_y);
				printf("atan2 en degre : %.2f) delta_ang : %.2f, delta_sprite_center : %.2f, centre du sprite (%.2f;%.2f) joueur (%.2f;%.2f)\n" ,rad_to_deg(atan2(dist_x, dist_y)), delta_ang, delta_sprite_center, dist_x, dist_y, g_su->p->player_x, g_su->p->player_y);
			++i;
		}
	
}

int which_sprite(char is_a_sprite)
{
	int i;

	i = -1;
	while (g_su->sprite_tab[++i])
		if (is_a_sprite == g_su->sprite_tab[i])
			return(g_su->sprite_tab[i]);
	return (0);
}

void init_vector2_d(t_vector2_d *tab)
{
	int i = -1;
	while (++i < 100)
	{
		tab[i].s_dist = 0;
		tab[i].s_impact = 0;
		tab[i].sprite = 0;
	}
}

void	join_sprites(t_player *p1, t_player *p2)
{
	t_vector2_d tab[100];
	int i;

	init_vector2_d(tab);
	i = 0;
	while ((p1->sprite_num >= 0 || p2->sprite_num >= 0) && i < 100)
	{
		if ((p1->sprite_num >= 0) && (p2->sprite_num >= 0))
		{
			tab[i].s_dist = p1->sprite_v2[p1->sprite_num].s_dist > p2->sprite_v2[p2->sprite_num].s_dist ? p1->sprite_v2[p1->sprite_num].s_dist : p2->sprite_v2[p2->sprite_num].s_dist;
			tab[i].sprite = tab[i].s_dist == p1->sprite_v2[p1->sprite_num].s_dist ? p1->sprite_v2[p1->sprite_num].sprite : p2->sprite_v2[p2->sprite_num].sprite;
			tab[i].s_dist == p1->sprite_v2[p1->sprite_num].s_dist ? --p1->sprite_num : --p2->sprite_num;
			if (tab[i].s_dist > p1->dist)
				continue;
			++i;
		}
		else
		{
			int boole = p1->sprite_num != -1 ? 1 : 2;
			if (p1->dist > boole == 1 ? p1->sprite_v2[p1->sprite_num].s_dist : p2->sprite_v2[p2->sprite_num].s_dist)
			{
				tab[i].s_dist = boole == 1 ? p1->sprite_v2[p1->sprite_num].s_dist : p2->sprite_v2[p2->sprite_num].s_dist;
				tab[i].sprite = boole == 1 ? p1->sprite_v2[p1->sprite_num].sprite : p2->sprite_v2[p2->sprite_num].sprite;
				boole == 1 ? --p1->sprite_num : --p2->sprite_num;
				if (tab[i].s_dist > p1->dist)
					continue;
				++i;
			}
		}
	}
	p1->sprite_num = i;
	i = 0;
	while (i < p1->sprite_num)
	{
		p1->sprite_v2[i].s_dist = tab[i].s_dist;
		p1->sprite_v2[i].sprite = tab[i].sprite;
		++i;
	}
}
/*
int main()
{
	t_player tab[2];
	tab[0].dist = 11.5;
	
	tab[0].sprite_v2[0].s_dist = 2;
	tab[0].sprite_v2[0].sprite = 2;//
	tab[0].sprite_v2[1].s_dist = 4;
	tab[0].sprite_v2[1].sprite = 4;//
	tab[0].sprite_v2[2].s_dist = 10;
	tab[0].sprite_v2[2].sprite = 10;//	
	tab[0].sprite_v2[3].s_dist = 15;
	tab[0].sprite_v2[3].sprite = 15;//

	tab[1].sprite_v2[0].s_dist = 3;
	tab[1].sprite_v2[0].sprite = 3;//
	tab[1].sprite_v2[1].s_dist = 5;
	tab[1].sprite_v2[1].sprite = 5;//
	tab[1].sprite_v2[2].s_dist = 11;
	tab[1].sprite_v2[2].sprite = 11;//
	tab[1].sprite_v2[3].s_dist = 11.2;
	tab[1].sprite_v2[3].sprite = 11;//
	tab[1].sprite_v2[4].s_dist = 16;
	tab[1].sprite_v2[4].sprite = 16;//
	tab[1].sprite_v2[5].s_dist = 19;
	tab[1].sprite_v2[5].sprite = 19;//

	tab[0].sprite_num = 3;
	tab[1].sprite_num = 5;

	init_vector2_d(tab[0].sprite_v2);
	init_vector2_d(tab[1].sprite_v2);
	join_sprites(&tab[0] , &tab[1]);

	int i = 0;
	while (i < tab[0].sprite_num)
	{
		printf("tab[0].sprite_v2[%d].s_dist : %f tab[0].sprite_v2[i].sprite : %d\n", i, tab[0].sprite_v2[i].s_dist , tab[0].sprite_v2[i].sprite);
		++i;
	}

}*/