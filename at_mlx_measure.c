#include "at_mlx_measure.h"

// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
// http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53



double horizontal_intersection(t_player *pl, double *tab)
{
	int 	y = tab[e_sin] > 0 ? (int)pl->player_y : (int)(pl->player_y + 1);
	double 	x = pl->player_x + (pl->player_y - y) / tab[e_tan];
	int		y_a = tab[e_sin] > 0 ? -1 : 1;
	double	x_a = -1 * y_a / tab[e_tan];
	int		ajusteur = tab[e_sin] > 0 ? -1 : 0;
	int		is_sprite = 0;
	int		i;

	init_vector2_d(pl->sprite_v2);
	i = 0;
	while (y < MAP_SIDE && y > 0 && x < MAP_SIDE && x > 0 && (g_su->map[y + ajusteur][(int)x] == '0' 
	|| (is_sprite  = which_sprite(g_su->map[y + ajusteur][(int)x]))))
	{
		if (is_sprite && i < 100)
		{
			pl->sprite_v2[i].s_dist = fabs((pl->player_x - x) / tab[e_cos]) * (cos(tab[e_x_rad]));
			pl->sprite_v2[i].s_impact = pl->wall_orient == NORD_vert ? x - (int)x : 1. - (x - (int)x);
			pl->sprite_v2[i].sprite = is_sprite;
			++i;
		}
		x += x_a;
		y += y_a;
	}
	pl->wall_orient = tab[e_sin] > 0 ? NORD_vert : SUD_rouge;
	pl->wall_impact = pl->wall_orient == NORD_vert ? x - (int)x : 1. - (x - (int)x);
	pl->sprite_num = i;
	return (fabs((pl->player_x - x) / tab[e_cos])); // <-- distance entre le joueur et le mur
}

double vertical_intersection(t_player *pl, double *tab)
{
	int 	x = tab[e_cos] < 0 ? (int)(pl->player_x): (int)(pl->player_x + 1);
	double 	y = pl->player_y + (pl->player_x - x) * tab[e_tan];
	int 	x_a = tab[e_cos] < 0  ? -1 : 1;
	double	y_a = -1 * x_a * tab[e_tan];
	int		ajusteur = tab[e_cos] < 0 ? -1 : 0;
	int		is_sprite = 0;
	int		i;

	init_vector2_d(pl->sprite_v2);
	i = 0;
	while (y < MAP_SIDE && y > 0 && x < MAP_SIDE && x > 0 && (g_su->map[(int)(y)][x + ajusteur] == '0'
	|| (is_sprite  = which_sprite(g_su->map[(int)(y)][x + ajusteur]))))
	{
		if (is_sprite && i < 100)
		{
			pl->sprite_v2[i].s_dist = fabs((pl->player_x - x) / tab[e_cos]) * (cos(tab[e_x_rad]));
			pl->sprite_v2[i].s_impact = pl->wall_orient == EST_bleu ? y - (int)y : 1. - (y - (int)y);
			pl->sprite_v2[i].sprite = is_sprite;
			++i;
		}
		x += x_a;
		y += y_a;
	}
	pl->wall_orient = tab[e_cos] < 0 ? OUEST_jaune : EST_bleu;
	pl->wall_impact = pl->wall_orient == EST_bleu ? y - (int)y : 1. - (y - (int)y);
	pl->sprite_num = i;
	return (fabs((pl->player_x - x) / tab[e_cos]));
}


double distance(t_player *pl, double x_rad)
{
	t_player p[2];
	double t[6];

	t[e_sin] = sin(pl->player_orient);
	t[e_cos] = cos(pl->player_orient);
	t[e_tan] = tan(pl->player_orient);
	t[e_x_rad] = x_rad;
	p[0] = *pl;
	p[1] = *pl;
	t[e_h] = horizontal_intersection(&p[0], t);
	t[e_v] = vertical_intersection(&p[1], t);
	*pl = t[e_h] < t[e_v] ? p[0] : p[1];
	pl->dist = cos(x_rad) * (t[e_h] < t[e_v] ? t[e_h] : t[e_v]);
	join_sprites(pl, t[e_h] > t[e_v] ? &p[0] : &p[1]); //si tu pars dqns une boucle infinie c'est ici revoie la fonction le sort ne marche pas du tout
	// tu compares entre slmt les deux valeur des l'index meme si je comprends pas encore pk ca cloche... aussi tu devrais uniquement envoyer le tab_vector2_d
	return (pl->dist);
}