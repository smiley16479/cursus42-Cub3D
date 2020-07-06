/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:07:17 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/02 12:21:59 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "at_mlx_sprite.h"

/*
** // distance du sprite et e_x_rad pour eviter ...
**	le fishEye -> distance entre le rayon et le sprite
**	pl->s_v2[t[4]].s_d = hypot(tab[8], tab[9]) * cos(tab[e_x_rad]);
**	ang_center_sprite = atan2(tab[9], tab[8]); // angle du centre du sprite
**	ang_sprite_impact = atan2(pl->pl_y - y, x - pl->pl_x);
** // diffrence angle du centre du sprite et celui du rayon actuel
**	delta_ang = atan_sur_360(ang_center_sprite - ang_sprite_impact);
** // ecart entre le centre du sprite et le point d'impact du rayon
**	pl->s_v2[t[4]].s_imp  = pl->s_v2[t[4]].s_d * tan(delta_ang) + 0.5;
*/

void	sprite(double *tab, int *t, t_player *pl)
{
	double ang_center_sprite;
	double delta_ang;
	double ang_sprite_impact;
	double x;
	double y;

	if (t[5])
	{
		x = tab[6];
		y = (double)t[0];
	}
	else
	{
		x = (double)t[0];
		y = tab[6];
	}
	pl->s_v2[t[4]].s_d = hypot(tab[8], tab[9]) * cos(tab[e_x_rad]);
	ang_center_sprite = atan2(tab[9], tab[8]);
	ang_sprite_impact = atan2(pl->pl_y - y, x - pl->pl_x);
	delta_ang = atan_sur_360(ang_center_sprite - ang_sprite_impact);
	pl->s_v2[t[4]].s_imp = pl->s_v2[t[4]].s_d * tan(delta_ang) + 0.5;
	pl->s_v2[t[4]].sprite = t[3];
	t[3] = 0;
	++t[4];
}

/*
** return(g_su->sprite_tab[i] - 48 - 1); // -48 pour les char;
**	- 1 pour concorder avec l'index des sprite du tableau
*/

int		which_sprite(char is_a_sprite)
{
	int i;

	i = -1;
	while (g_su->sprite_tab[++i])
		if (is_a_sprite == g_su->sprite_tab[i])
			return (g_su->sprite_tab[i] - '0' - 1);
	return (0);
}

void	init_vector2_d(t_vector2_d *tab, int borne)
{
	int i;

	i = -1;
	while (++i < borne)
	{
		tab[i].s_d = 0;
		tab[i].s_imp = 0;
		tab[i].sprite = 0;
	}
}

void	join_sprites_sub_func(t_player *p1, t_player *p2,
									t_vector2_d *tab, int *t)
{
	while ((p1->s_num >= 0 || p2->s_num >= 0) && t[0] < 100)
		if (p1->s_num >= 0 && p2->s_num >= 0)
		{
			tab[t[0]] = p1->s_v2[p1->s_num].s_d > p2->s_v2[p2->s_num].s_d ?
			p1->s_v2[p1->s_num] : p2->s_v2[p2->s_num];
			tab[t[0]].s_d == p1->s_v2[p1->s_num].s_d ?
			--p1->s_num : --p2->s_num;
			if (tab[t[0]].s_d > p1->dist)
				continue;
			++t[0];
		}
		else
		{
			t[1] = p1->s_num != -1 ? 1 : 2;
			if ((p1->dist > t[1]) == 1 ?
			p1->s_v2[p1->s_num].s_d : p2->s_v2[p2->s_num].s_d)
			{
				tab[t[0]] = t[1] == 1 ?
				p1->s_v2[p1->s_num] : p2->s_v2[p2->s_num];
				t[1] == 1 ? --p1->s_num : --p2->s_num;
				if (tab[t[0]].s_d > p1->dist)
					continue;
				++t[0];
			}
		}
}

void	join_sprites(t_player *p1, t_player *p2)
{
	t_vector2_d	tab[100];
	int			t[2];

	t[0] = 0;
	init_vector2_d(tab, 100);
	join_sprites_sub_func(p1, p2, tab, t);
	p1->s_num = t[0] != 0 ? t[0] : p1->s_num;
	t[0] = 0;
	while (t[0] <= p1->s_num)
	{
		p1->s_v2[p1->s_num - t[0]] = tab[t[0]];
		++t[0];
	}
}

/*
**	int main()
**	{
**	t_player tab[2];
**	tab[0].dist = 11.5;
**
**	init_vector2_d(tab[0].s_v2);
**	init_vector2_d(tab[1].s_v2);
**
**	tab[0].s_v2[0].s_d = 2;
**	tab[0].s_v2[0].sprite = 2;//
**	tab[0].s_v2[1].s_d = 4;
**	tab[0].s_v2[1].sprite = 4;//
**	tab[0].s_v2[2].s_d = 10;
**	tab[0].s_v2[2].sprite = 10;//
**	tab[0].s_v2[3].s_d = 15;
**	tab[0].s_v2[3].sprite = 15;//
**
**	tab[1].s_v2[0].s_d = 3;
**	tab[1].s_v2[0].sprite = 3;//
**	tab[1].s_v2[1].s_d = 5;
**	tab[1].s_v2[1].sprite = 5;//
**	tab[1].s_v2[2].s_d = 11;
**	tab[1].s_v2[2].sprite = 11;//
**	tab[1].s_v2[3].s_d = 11.2;
**	tab[1].s_v2[3].sprite = 11;//
**	tab[1].s_v2[4].s_d = 16;
**	tab[1].s_v2[4].sprite = 16;//
**	tab[1].s_v2[5].s_d = 19;
**	tab[1].s_v2[5].sprite = 19;//
**
**	tab[0].s_num = 3;
**	tab[1].s_num = 5;
**	join_sprites(&tab[0] , &tab[1]);
**
**	int i = 0;
**	while (i < tab[0].s_num)
**	{
**		printf("tab[0].s_v2[%d].s_d : %f tab[0].s_v2[i].sprite : %d\n",
**		i, tab[0].s_v2[i].s_d , tab[0].s_v2[i].sprite);
**		++i;
**	}
**
**	}
*/
