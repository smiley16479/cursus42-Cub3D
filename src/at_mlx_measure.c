/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_measure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:51:12 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/01 16:57:20 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_mlx_measure.h"

/*
** http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/
**	affichage/3d/raycasting/theorie/04-detection_des_murs
** http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53
*/

void	init_tab(int *t, double *tab, t_player *pl, int hor_ver)
{
	if (hor_ver)
	{
		t[0] = tab[e_sin] > 0 ? (int)pl->pl_y : (int)(pl->pl_y + 1);
		tab[6] = pl->pl_x + (pl->pl_y - t[0]) / tab[e_tan];
		t[1] = tab[e_sin] > 0 ? -1 : 1;
		t[2] = tab[e_sin] > 0 ? -1 : 0;
		tab[7] = -1 * t[1] / tab[e_tan];
	}
	else
	{
		t[0] = tab[e_cos] < 0 ? (int)(pl->pl_x) : (int)(pl->pl_x + 1);
		tab[6] = pl->pl_y + (pl->pl_x - t[0]) * tab[e_tan];
		t[1] = tab[e_cos] < 0 ? -1 : 1;
		t[2] = tab[e_cos] < 0 ? -1 : 0;
		tab[7] = -1 * t[1] * tab[e_tan];
	}
	t[3] = 0;
	t[4] = 0;
}

double	horizontal_intersection(t_player *pl, double *tab)
{
	int		t[6];

	init_tab(t, tab, pl, 1);
	init_vector2_d(pl->s_v2, 100);
	while (0 < t[0] && t[0] < g_su->ms.y && 0 < tab[6] &&
	tab[6] < g_su->ms.x && (g_su->map[t[0] + t[2]][(int)tab[6]] == '0' ||
	(t[3] = which_sprite(g_su->map[t[0] + t[2]][(int)tab[6]]))))
	{
		if (t[3] && t[4] < 100)
		{
			t[5] = 1;
			tab[8] = (int)tab[6] + .5 - pl->pl_x;
			tab[9] = pl->pl_y - (t[0] + t[2] + .5);
			sprite(tab, t, pl);
		}
		tab[6] += tab[7];
		t[0] += t[1];
	}
	pl->w_o = tab[e_sin] > 0 ? NORD_vert : SUD_rouge;
	pl->wall_impact = pl->w_o == NORD_vert ? tab[6] - (int)tab[6] :
	1. - (tab[6] - (int)tab[6]);
	pl->s_num = t[4] - 1;
	return (fabs((pl->pl_x - tab[6]) / tab[e_cos]));
}

double	vertical_intersection(t_player *pl, double *tab)
{
	int		t[6];

	init_tab(t, tab, pl, 0);
	init_vector2_d(pl->s_v2, 100);
	while (tab[6] < g_su->ms.y && tab[6] > 0 && t[0] < g_su->ms.x &&
	t[0] > 0 && (g_su->map[(int)tab[6]][t[0] + t[2]] == '0' ||
	(t[3] = which_sprite(g_su->map[(int)tab[6]][t[0] + t[2]]))))
	{
		if (t[3] && t[4] < 100)
		{
			t[5] = 0;
			tab[8] = t[0] + t[2] + .5 - pl->pl_x;
			tab[9] = pl->pl_y - (int)tab[6] - .5;
			sprite(tab, t, pl);
		}
		t[0] += t[1];
		tab[6] += tab[7];
	}
	pl->w_o = tab[e_cos] < 0 ? OUEST_jaune : EST_bleu;
	pl->wall_impact = pl->w_o == EST_bleu ?
	tab[6] - (int)tab[6] : 1. - (tab[6] - (int)tab[6]);
	pl->s_num = t[4] - 1;
	return (fabs((pl->pl_x - t[0]) / tab[e_cos]));
}

double	distance(t_player *pl, double x_rad)
{
	t_player	p[2];
	double		tab[10];

	tab[e_sin] = sin(pl->player_orient);
	tab[e_cos] = cos(pl->player_orient);
	tab[e_tan] = tan(pl->player_orient);
	tab[e_x_rad] = x_rad;
	p[0] = *pl;
	p[1] = *pl;
	tab[e_h] = horizontal_intersection(&p[0], tab);
	tab[e_v] = vertical_intersection(&p[1], tab);
	*pl = tab[e_h] < tab[e_v] ? p[0] : p[1];
	pl->dist = cos(x_rad) * (tab[e_h] < tab[e_v] ? tab[e_h] : tab[e_v]);
	join_sprites(pl, tab[e_h] > tab[e_v] ? &p[0] : &p[1]);
	return (pl->dist);
}

/*
**	//horizontal
** 	int 	y 			= tab[e_sin] > 0 ? (int)pl->pl_y : (int)(pl->pl_y + 1);
**	double 	x 			= pl->pl_x + (pl->pl_y - y) / tab[e_tan];
**	int		y_a 		= tab[e_sin] > 0 ? -1 : 1;
**	double	x_a 		= -1 * y_a / tab[e_tan];
**	int		ajusteur 	= tab[e_sin] > 0 ? -1 : 0;
**	int		is_sprite 	= 0;
**	int		i 			= 0;
**	//vertical
** 	int 	x = tab[e_cos] < 0 ? (int)(pl->pl_x): (int)(pl->pl_x + 1);
**	double 	y = pl->pl_y + (pl->pl_x - x) * tab[e_tan];
**	int 	x_a = tab[e_cos] < 0  ? -1 : 1;
**	double	y_a = -1 * x_a * tab[e_tan];
**	int		ajusteur = tab[e_cos] < 0 ? -1 : 0;
**	int		is_sprite = 0;
**	int		i = 0;
*/
