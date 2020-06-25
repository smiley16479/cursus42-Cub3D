#include "at_mlx_measure.h"

// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
// http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53


int sprite(double *tab, int *is_sprite, int *i, int ajusteur, t_player *pl, double x, double y,
double dist_x, double dist_y, int POV)
{
	double ang_center_sprite, delta_ang,  ang_sprite_impact;

	pl->sprite_v2[*i].s_dist = hypot(dist_x, dist_y) * cos(tab[e_x_rad]); // distance du sprite et e_x_rad pour eviter le fishEye -> distance entre le rayon et le sprite
	ang_center_sprite = atan2(dist_y, dist_x); // angle du centre du sprite
	ang_sprite_impact = atan2(pl->pl_y - y, x - pl->pl_x);
	//ANGLE SPRITE IMPACT A L'AIR DE DECONNER NE DEVRAIT IL PAS CHANGER MEME EN SE DEPLACANT LATTERALEMENT DU SPRITE (Q-D)
	delta_ang = atan_sur_360(ang_center_sprite - ang_sprite_impact); // diffrence angle du centre du sprite et celui du rayon actuel

	pl->sprite_v2[*i].s_impact  = pl->sprite_v2[*i].s_dist * tan(delta_ang) /* * cos(tab[e_x_rad]) */ + 0.5; // ecart entre le centre du sprite et le point d'impact du rayon
	pl->sprite_v2[*i].sprite = *is_sprite;
	*is_sprite = 0;
	// if (-0.01 <= tab[e_x_rad] && tab[e_x_rad] <= 0.01)
	// {
		// POV == 1 ? printf("ver_ ") : printf("hor_ ");
		// POV == 1 ? printf("pos_sprite %d;%d player (%.1f;%.1f), dist_sprite : (%.1f,%.1f), pl->sprite_v2[0].s_dist : %.4f\n" ,(int)x + ajusteur , (int)(y), pl->pl_x, pl->pl_y, dist_x, dist_y, pl->sprite_v2[0].s_dist) 
				// : printf("pos_sprite %d;%d player (%.1f;%.1f), dist_sprite : (%.1f,%.1f), pl->sprite_v2[0].s_dist : %.4f\n", (int)x , (int)y + ajusteur, pl->pl_x, pl->pl_y, dist_x, dist_y, pl->sprite_v2[0].s_dist);
		// printf("ang_center_sprite : %6.3f, ang_sprite_impact : %6.3f, delta_angle : %-6.3f, e_x_rad : %6.3f, pl->orient : %6.3f, pl->orient_origin : %6.3f\n", rad_to_deg(ang_center_sprite), rad_to_deg(ang_sprite_impact), rad_to_deg(delta_ang), rad_to_deg(tab[e_x_rad]), rad_to_deg(pl->player_orient), rad_to_deg(pl->player_orient_origin));
		// printf("pl->sprite_v2[0].s_impact : %f\n",pl->sprite_v2[0].s_impact);
		// printf("pl->sprite_v2[0].sprite : %d\n",pl->sprite_v2[0].sprite);
		// printf("pl->sprite_v2[0].s_dist : %f, pl->dist : %f\n",pl->sprite_v2[0].s_dist, pl->dist);
	// }
	++*i;
}

double horizontal_intersection(t_player *pl, double *tab)
{
	int 	y = tab[e_sin] > 0 ? (int)pl->pl_y : (int)(pl->pl_y + 1);
	double 	x = pl->pl_x + (pl->pl_y - y) / tab[e_tan];
	int		y_a = tab[e_sin] > 0 ? -1 : 1;
	double	x_a = -1 * y_a / tab[e_tan];
	int		ajusteur = tab[e_sin] > 0 ? -1 : 0;
	int		is_sprite = 0;
	int		i = 0;

	init_vector2_d(pl->sprite_v2, 100);
	while (0 < y && y < g_su->ms.y && 0 < x && x < g_su->ms.x && (g_su->map[y + ajusteur][(int)x] == '0' 
	|| (is_sprite = which_sprite(g_su->map[y + ajusteur][(int)x]))))
	{
		if (is_sprite && i < 100)
			sprite(tab, &is_sprite, &i, ajusteur, pl, x, (double)y,
			// pl->pl_x - (int)x - .5,
			(int)x + .5 - pl->pl_x,
			// y + ajusteur + .5 - pl->pl_y,
			pl->pl_y - (y + ajusteur + .5),
			0);
			
		x += x_a;
		y += y_a;
	}
	pl->wall_orient = tab[e_sin] > 0 ? NORD_vert : SUD_rouge;
	pl->wall_impact = pl->wall_orient == NORD_vert ? x - (int)x : 1. - (x - (int)x);
	pl->s_num = i - 1;
	return (fabs((pl->pl_x - x) / tab[e_cos])); // <-- distance entre le joueur et le mur
}

double vertical_intersection(t_player *pl, double *tab)
{
	// int		t[5]; // x, x_a, ajusteur, is_sprite, i 
	// double	ta[2];

	int 	x = tab[e_cos] < 0 ? (int)(pl->pl_x): (int)(pl->pl_x + 1);
	double 	y = pl->pl_y + (pl->pl_x - x) * tab[e_tan];
	int 	x_a = tab[e_cos] < 0  ? -1 : 1;
	double	y_a = -1 * x_a * tab[e_tan];
	int		ajusteur = tab[e_cos] < 0 ? -1 : 0;
	int		is_sprite = 0;
	int		i = 0;
/*
	t[0] = tab[e_cos] < 0 ? (int)(pl->pl_x): (int)(pl->pl_x + 1);
	ta[0] = pl->pl_y + (pl->pl_x - t[0]) * tab[e_tan];
	t[1] = tab[e_cos] < 0  ? -1 : 1;
	ta[1] = -1 * t[1] * tab[e_tan];
	t[2] = tab[e_cos] < 0 ? -1 : 0;
	t[3] = 0;
	t[4] = 0;
*/
	init_vector2_d(pl->sprite_v2, 100);
	while (y < g_su->ms.y && y > 0 && x < g_su->ms.x && x > 0 && (g_su->map[(int)y][x + ajusteur] == '0'
	|| (is_sprite = which_sprite(g_su->map[(int)y][x + ajusteur]))))
	{
		if (is_sprite && i < 100)
			sprite(tab, &is_sprite, &i, ajusteur, pl, (double)x, y,
			x + ajusteur + .5 - pl->pl_x,
			pl->pl_y - (int)y - .5,
			1);
		x += x_a;
		y += y_a;
	}
	pl->wall_orient = tab[e_cos] < 0 ? OUEST_jaune : EST_bleu;
	pl->wall_impact = pl->wall_orient == EST_bleu ? y - (int)y : 1. - (y - (int)y);
	pl->s_num = i - 1;
	return (fabs((pl->pl_x - x) / tab[e_cos]));
}

double distance(t_player *pl, double x_rad)
{
	t_player p[2];
	double t[6]; // ajout de 2 pour dist_x et dist_y

	t[e_sin] = sin(pl->player_orient);
	t[e_cos] = cos(pl->player_orient);
	t[e_tan] = tan(pl->player_orient);
	t[e_x_rad] = x_rad;
	p[0] = *pl;
	p[1] = *pl;
	t[e_h] = horizontal_intersection(&p[0], t);
	t[e_v] = vertical_intersection(&p[1], t);
	*pl = t[e_h] < t[e_v] ? p[0] : p[1];
	pl->dist = cos(x_rad)  * (t[e_h] < t[e_v] ? t[e_h] : t[e_v]);
// !!!!  REVOIE TA FONCTION JOIN_SPRITE ELLE EST SERIEUSEMENT MAUVAISE
		join_sprites(pl, t[e_h] > t[e_v] ? &p[0] : &p[1]); //si tu pars dqns une boucle infinie c'est ici revoie la fonction le sort ne marche pas du tout elle ralentit tout
	// tu compares entre slmt les deux valeur des l'index meme si je comprends pas encore pk ca cloche... aussi tu devrais uniquement envoyer le tab_vector2_d
	return (pl->dist);
}