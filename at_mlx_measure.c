#include "at_mlx_measure.h"

// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
// http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53


double horizontal_intersection(t_player *pl, double *tab)
{
	double 	y = tab[e_sin] > 0 ? (int)pl->player_y : (int)(pl->player_y + 1);
	double 	x = pl->player_x + (pl->player_y - y) / tab[e_tan];
	double	y_a = tab[e_sin] > 0 ? -1 : 1;
	double	x_a = -1 * y_a / tab[e_tan];
	int		ajusteur = tab[e_sin] > 0 ? -1 : 0;

	while (y < MAP_SIDE && y > 0 && x < MAP_SIDE && x > 0 && pl->map[(int)y + ajusteur][(int)x] == '0')
	{
		pl->wall_impact += x_a; 
		x += x_a;
		y += y_a;
	}
	pl->wall_orient = tab[e_sin] > 0 ? NORD_vert : SUD_rouge;
	pl->wall_impact = pl->wall_orient == NORD_vert ? x - (int)x : 1. - (x - (int)x) ;
	return (fabs((pl->player_x - x) / tab[e_cos])); // <-- distance entre le joueur et le mur
}

double vertical_intersection(t_player *pl, double *tab)
{
	int 	x = tab[e_cos] < 0 ? (int)(pl->player_x): (int)(pl->player_x + 1);
	double 	y = pl->player_y + (pl->player_x - x) * tab[e_tan];
	int 	x_a = tab[e_cos] < 0  ? -1 : 1;
	double	y_a = -1 * x_a * tab[e_tan];
	int		ajusteur = tab[e_cos] < 0 ? -1 : 0;

	while (y < MAP_SIDE && y > 0 && x < MAP_SIDE && x > 0 && pl->map[(int)(y)][x + ajusteur] == '0')
	{
		x += x_a;
		y += y_a;
	}
	pl->wall_orient = tab[e_cos] < 0 ? OUEST_jaune : EST_bleu;
	pl->wall_impact = pl->wall_orient == EST_bleu ? y - (int)y : 1. - (y - (int)y);
	return (fabs((pl->player_x - x) / tab[e_cos]));
}

double d_incorrecte(t_player *pl)
{
	t_player p[2];
	double tab[5];

	tab[e_sin] = sin(pl->player_orient);
	tab[e_cos] = cos(pl->player_orient);
	tab[e_tan] = tan(pl->player_orient);
	p[0] = *pl; //c'est pas bon tu copies toute la map au passage bref c pas bon : pas bon !!!
	p[1] = *pl;
	tab[e_h] = horizontal_intersection(&p[0], tab);
	tab[e_v] = vertical_intersection(&p[1], tab);
	*pl = tab[e_h] < tab[e_v] ? p[0] : p[1];
	return (tab[e_h] < tab[e_v] ? tab[e_h] : tab[e_v]);
}