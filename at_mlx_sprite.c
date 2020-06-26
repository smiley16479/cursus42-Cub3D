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

/* void sprite_process(int x, int ajusteur, double y, double *tab)
{ //pale copie de l'ebauche faite ds measure.c a adapter/ameliorer
	int		is_sprite = 0;
	int		i;
	if ((is_sprite = which_sprite(g_su->map[(int)y][x + ajusteur])) && i < 100)
	{
		double dist_x, dist_y, delta_ang, delta_sprite_center;
		// dist_x = fabs(pl->pl_x - (x + (tab[e_cos] < 0 ? -.5 : .5)));
		// dist_y = fabs(pl->pl_y - ((int)y + (tab[e_sin] < 0 ? -.5 : .5)));
		dist_x = fabs(x + ajusteur + .5 - g_su->p->pl_x); //tab[e_cos] > 0 ? x + ajusteur + .5 - pl->pl_x : pl->pl_x - (x + ajusteur) - .5; 
		dist_y = fabs(g_su->p->pl_y - (int)y - .5); //tab[e_sin] > 0 ? pl->pl_y - (int)y - .5 : (int)y - pl->pl_y + .5;
		delta_ang = atan2(dist_x, dist_y) - g_su->p->player_orient;
		g_su->p->s_v2[i].s_dist = hypot(dist_x, dist_y); //fabs((pl->pl_x - x + tab[e_cos] < 0 ? -.5 : .5) / tab[e_cos]) * cos(tab[e_x_rad]);
		delta_sprite_center = g_su->p->s_v2[i].s_dist * tan(delta_ang); // ecart entre le centre du sprite et le point d'impact du rayon
		g_su->p->s_v2[i].s_dist = g_su->p->s_v2[i].s_dist * cos(delta_ang); // pour eviter le fishEye -> distance entre le rayon et le sprite
		g_su->p->s_v2[i].s_imp = delta_sprite_center; // g_su->p->w_o == EST_bleu ? y - (int)y : 1. - (y - (int)y);
		g_su->p->s_v2[i].sprite = is_sprite;
		if (-0.01 <= tab[e_x_rad] && tab[e_x_rad] <= 0.01)
			// printf("orient : %f, x_rad : %f, dist_x : %f, dist_y : %f, g_su->p->s_v2[i].s_dist(hypot) : %f, is_sprite %d;%d player (%.1f;%.1f)\n" ,rad_to_deg(g_su->p->player_orient_origin), tab[e_x_rad] ,dist_x, dist_y, g_su->p->s_v2[i].s_dist, x + ajusteur , (int)(y), g_su->p->pl_x, g_su->p->pl_y);
			printf("atan2 en degre : %.2f) delta_ang : %.2f, delta_sprite_center : %.2f, centre du sprite (%.2f;%.2f) joueur (%.2f;%.2f)\n" ,rad_to_deg(atan2(dist_x, dist_y)), delta_ang, delta_sprite_center, dist_x, dist_y, g_su->p->pl_x, g_su->p->pl_y);
		++i;
	}
	
}
*/
int which_sprite(char is_a_sprite)
{
	int i;

	i = -1;
	while (g_su->sprite_tab[++i])
		if (is_a_sprite == g_su->sprite_tab[i])
			return(g_su->sprite_tab[i] - 48 - 1); // -48 pour les char ; - 1 pour concorder avec l'index des sprite du tableau
	return (0);
} 

void init_vector2_d(t_vector2_d *tab, int borne)
{
	int i = -1;
	while (++i < borne)
	{
		tab[i].s_dist = 0;
		tab[i].s_imp = 0;
		tab[i].sprite = 0;
	}
}

void	join_sprites(t_player *p1, t_player *p2)
{
	t_vector2_d tab[100];
	int i;
	int boole;
	init_vector2_d(tab, 100);
	i = 0;
	while ((p1->s_num >= 0 || p2->s_num >= 0) && i < 100)
	{
		if (p1->s_num >= 0 && p2->s_num >= 0)
		{
			tab[i] = p1->s_v2[p1->s_num].s_dist > p2->s_v2[p2->s_num].s_dist ? p1->s_v2[p1->s_num] : p2->s_v2[p2->s_num];
			tab[i].s_dist == p1->s_v2[p1->s_num].s_dist ? --p1->s_num : --p2->s_num;
			if (tab[i].s_dist > p1->dist)
				continue;
			++i;
		}
		else
		{
			boole = p1->s_num != -1 ? 1 : 2;
			if (p1->dist > boole == 1 ? p1->s_v2[p1->s_num].s_dist : p2->s_v2[p2->s_num].s_dist)
			{
				tab[i] = boole == 1 ? p1->s_v2[p1->s_num]: p2->s_v2[p2->s_num];
				boole == 1 ? --p1->s_num : --p2->s_num;
				if (tab[i].s_dist > p1->dist)
					continue;
				++i;
			}
		}
	}
	p1->s_num = i != 0 ? i : p1->s_num;
	i = 0;
	while (i <= p1->s_num)
	{
		p1->s_v2[p1->s_num - i]  = tab[i];
		++i;
	}
}

/* int main()
{
	t_player tab[2];
	tab[0].dist = 11.5;

	init_vector2_d(tab[0].s_v2);
	init_vector2_d(tab[1].s_v2);
	
	tab[0].s_v2[0].s_dist = 2;
	tab[0].s_v2[0].sprite = 2;//
	tab[0].s_v2[1].s_dist = 4;
	tab[0].s_v2[1].sprite = 4;//
	tab[0].s_v2[2].s_dist = 10;
	tab[0].s_v2[2].sprite = 10;//	
	tab[0].s_v2[3].s_dist = 15;
	tab[0].s_v2[3].sprite = 15;//

	tab[1].s_v2[0].s_dist = 3;
	tab[1].s_v2[0].sprite = 3;//
	tab[1].s_v2[1].s_dist = 5;
	tab[1].s_v2[1].sprite = 5;//
	tab[1].s_v2[2].s_dist = 11;
	tab[1].s_v2[2].sprite = 11;//
	tab[1].s_v2[3].s_dist = 11.2;
	tab[1].s_v2[3].sprite = 11;//
	tab[1].s_v2[4].s_dist = 16;
	tab[1].s_v2[4].sprite = 16;//
	tab[1].s_v2[5].s_dist = 19;
	tab[1].s_v2[5].sprite = 19;//

	tab[0].s_num = 3;
	tab[1].s_num = 5;
	join_sprites(&tab[0] , &tab[1]);

	int i = 0;
	while (i < tab[0].s_num)
	{
		printf("tab[0].s_v2[%d].s_dist : %f tab[0].s_v2[i].sprite : %d\n", i, tab[0].s_v2[i].s_dist , tab[0].s_v2[i].sprite);
		++i;
	}

} */