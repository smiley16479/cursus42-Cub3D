#include "at_mlx_measure.h"

// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
// http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53


int sprite(double *tab, int *is_sprite, int *i, t_player *pl, double x, double y,
double dist_x, double dist_y)
{
	double ang_center_sprite, delta_ang,  ang_sprite_impact;

	pl->s_v2[*i].s_dist = hypot(dist_x, dist_y) * cos(tab[e_x_rad]); // distance du sprite et e_x_rad pour eviter le fishEye -> distance entre le rayon et le sprite
	ang_center_sprite = atan2(dist_y, dist_x); // angle du centre du sprite
	ang_sprite_impact = atan2(pl->pl_y - y, x - pl->pl_x);
	//ANGLE SPRITE IMPACT A L'AIR DE DECONNER NE DEVRAIT IL PAS CHANGER MEME EN SE DEPLACANT LATTERALEMENT DU SPRITE (Q-D)
	delta_ang = atan_sur_360(ang_center_sprite - ang_sprite_impact); // diffrence angle du centre du sprite et celui du rayon actuel

	pl->s_v2[*i].s_imp  = pl->s_v2[*i].s_dist * tan(delta_ang) /* * cos(tab[e_x_rad]) */ + 0.5; // ecart entre le centre du sprite et le point d'impact du rayon
	pl->s_v2[*i].sprite = *is_sprite;
	*is_sprite = 0;
	// if (-0.01 <= tab[e_x_rad] && tab[e_x_rad] <= 0.01)
	// {
		// POV == 1 ? printf("ver_ ") : printf("hor_ ");
		// POV == 1 ? printf("pos_sprite %d;%d player (%.1f;%.1f), dist_sprite : (%.1f,%.1f), pl->s_v2[0].s_dist : %.4f\n" ,(int)x + ajusteur , (int)(y), pl->pl_x, pl->pl_y, dist_x, dist_y, pl->s_v2[0].s_dist) 
				// : printf("pos_sprite %d;%d player (%.1f;%.1f), dist_sprite : (%.1f,%.1f), pl->s_v2[0].s_dist : %.4f\n", (int)x , (int)y + ajusteur, pl->pl_x, pl->pl_y, dist_x, dist_y, pl->s_v2[0].s_dist);
		// printf("ang_center_sprite : %6.3f, ang_sprite_impact : %6.3f, delta_angle : %-6.3f, e_x_rad : %6.3f, pl->orient : %6.3f, pl->orient_origin : %6.3f\n", rad_to_deg(ang_center_sprite), rad_to_deg(ang_sprite_impact), rad_to_deg(delta_ang), rad_to_deg(tab[e_x_rad]), rad_to_deg(pl->player_orient), rad_to_deg(pl->player_orient_origin));
		// printf("pl->s_v2[0].s_imp : %f\n",pl->s_v2[0].s_imp);
		// printf("pl->s_v2[0].sprite : %d\n",pl->s_v2[0].sprite);
		// printf("pl->s_v2[0].s_dist : %f, pl->dist : %f\n",pl->s_v2[0].s_dist, pl->dist);
	// }
	++*i;
}

void init_tab(int *t, double *tab, t_player *pl, int hor_ver)
{
// horizontal
	if (hor_ver)
	{
		t[0] = tab[e_sin] > 0 ? (int)pl->pl_y : (int)(pl->pl_y + 1);
		tab[6] = pl->pl_x + (pl->pl_y - t[0]) / tab[e_tan];
		t[1] = tab[e_sin] > 0 ? -1 : 1;
		t[2] = tab[e_sin] > 0 ? -1 : 0;
		tab[7] = -1 * t[1] / tab[e_tan];
	}
//verticale
	else 
	{
		t[0] = tab[e_cos] < 0 ? (int)(pl->pl_x): (int)(pl->pl_x + 1);
		tab[6] = pl->pl_y + (pl->pl_x - t[0]) * tab[e_tan];
		t[1] = tab[e_cos] < 0  ? -1 : 1;
		t[2] = tab[e_cos] < 0 ? -1 : 0;
		tab[7] = -1 * t[1] * tab[e_tan];
	}
	t[3] = 0;
	t[4] = 0;
}

double horizontal_intersection(t_player *pl, double *tab)
{
	int		t[5]; 
	// double	ta[2];

/* 	int 	y 			= tab[e_sin] > 0 ? (int)pl->pl_y : (int)(pl->pl_y + 1);
	double 	x 			= pl->pl_x + (pl->pl_y - y) / tab[e_tan];
	int		y_a 		= tab[e_sin] > 0 ? -1 : 1;
	double	x_a 		= -1 * y_a / tab[e_tan];
	int		ajusteur 	= tab[e_sin] > 0 ? -1 : 0;
	int		is_sprite 	= 0;
	int		i 			= 0; 

	t[0] = tab[e_sin] > 0 ? (int)pl->pl_y : (int)(pl->pl_y + 1);
	tab[6] = pl->pl_x + (pl->pl_y - t[0]) / tab[e_tan];
	t[1] = tab[e_sin] > 0 ? -1 : 1;
	tab[7] = -1 * t[1] / tab[e_tan];
	t[2] = tab[e_sin] > 0 ? -1 : 0;
	t[3] = 0;
	t[4] = 0;*/

	init_tab(t, tab, pl, 1);
	init_vector2_d(pl->s_v2, 100);
	while (0 < t[0] && t[0] < g_su->ms.y && 0 < tab[6] &&
	tab[6] < g_su->ms.x && (g_su->map[t[0] + t[2]][(int)tab[6]] == '0' ||
	(t[3] = which_sprite(g_su->map[t[0] + t[2]][(int)tab[6]]))))
	{
		if (t[3] && t[4] < 100)
			sprite(tab, &t[3], &t[4], pl, tab[6], (double)t[0],
			(int)tab[6] + .5 - pl->pl_x,
			pl->pl_y - (t[0] + t[2] + .5));
			
		tab[6] += tab[7];
		t[0] += t[1];
	}
	pl->w_o = tab[e_sin] > 0 ? NORD_vert : SUD_rouge;
	pl->wall_impact = pl->w_o == NORD_vert ? tab[6] - (int)tab[6] : 1. - (tab[6] - (int)tab[6]);
	pl->s_num = t[4] - 1;
	return (fabs((pl->pl_x - tab[6]) / tab[e_cos])); // <-- distance entre le joueur et le mur
}

double vertical_intersection(t_player *pl, double *tab)
{
	int		t[5]; // x, x_a, ajusteur, is_sprite, i 
	// double	ta[2];

/* 	int 	x = tab[e_cos] < 0 ? (int)(pl->pl_x): (int)(pl->pl_x + 1);
	double 	y = pl->pl_y + (pl->pl_x - x) * tab[e_tan];
	int 	x_a = tab[e_cos] < 0  ? -1 : 1;
	double	y_a = -1 * x_a * tab[e_tan];
	int		ajusteur = tab[e_cos] < 0 ? -1 : 0;
	int		is_sprite = 0;
	int		i = 0;

	t[0] = tab[e_cos] < 0 ? (int)(pl->pl_x): (int)(pl->pl_x + 1);
	tab[6] = pl->pl_y + (pl->pl_x - t[0]) * tab[e_tan];
	t[1] = tab[e_cos] < 0  ? -1 : 1;
	tab[7] = -1 * t[1] * tab[e_tan];
	t[2] = tab[e_cos] < 0 ? -1 : 0;
	t[3] = 0;
	t[4] = 0; */

	init_tab(t, tab, pl, 0);
	init_vector2_d(pl->s_v2, 100);
	while (tab[6] < g_su->ms.y && tab[6] > 0 && t[0] < g_su->ms.x &&
	t[0] > 0 && (g_su->map[(int)tab[6]][t[0] + t[2]] == '0' ||
	(t[3] = which_sprite(g_su->map[(int)tab[6]][t[0] + t[2]]))))
	{
		if (t[3] && t[4] < 100)
			sprite(tab, &(t[3]), &(t[4]), pl, (double)t[0], tab[6],
			t[0] + t[2] + .5 - pl->pl_x, pl->pl_y - (int)tab[6] - .5);
		t[0] += t[1];
		tab[6] += tab[7];
	}
	pl->w_o = tab[e_cos] < 0 ? OUEST_jaune : EST_bleu;
	pl->wall_impact = pl->w_o == EST_bleu ?
	tab[6] - (int)tab[6] : 1. - (tab[6] - (int)tab[6]);
	pl->s_num = t[4] - 1;
	return (fabs((pl->pl_x - t[0]) / tab[e_cos]));
}

double distance(t_player *pl, double x_rad)
{
	t_player p[2];
	double tab[8];

	tab[e_sin] = sin(pl->player_orient);
	tab[e_cos] = cos(pl->player_orient);
	tab[e_tan] = tan(pl->player_orient);
	tab[e_x_rad] = x_rad;
	p[0] = *pl;
	p[1] = *pl;
	tab[e_h] = horizontal_intersection(&p[0], tab);
	tab[e_v] = vertical_intersection(&p[1], tab);
	*pl = tab[e_h] < tab[e_v] ? p[0] : p[1];
	pl->dist = cos(x_rad)  * (tab[e_h] < tab[e_v] ? tab[e_h] : tab[e_v]);
	join_sprites(pl, tab[e_h] > tab[e_v] ? &p[0] : &p[1]);
	return (pl->dist);
}