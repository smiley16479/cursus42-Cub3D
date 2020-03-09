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
	int		i = -1;
	int		is_sprite = 0;
	while (++i < 100)
	{
		pl->sprite_v2[i].s_dist = 0;
		pl->sprite_v2[i].s_impact = 0;
		pl->sprite_v2[i].sprite = 0; 
	}
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
	int		i = -1;
	int		is_sprite = 0;
	while (++i < 100)
	{
		pl->sprite_v2[i].s_dist = 0;
		pl->sprite_v2[i].s_impact = 0;
		pl->sprite_v2[i].sprite = 0; 
	}
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
	double tab[6];

	tab[e_sin] = sin(pl->player_orient);
	tab[e_cos] = cos(pl->player_orient);
	tab[e_tan] = tan(pl->player_orient);
	tab[e_x_rad] = x_rad;
	p[0] = *pl; //c'est pas bon tu copies toute la map au passage bref c pas bon : pas bon !!!
	p[1] = *pl;
	tab[e_h] = horizontal_intersection(&p[0], tab);
	tab[e_v] = vertical_intersection(&p[1], tab);
	*pl = tab[e_h] < tab[e_v] ? p[0] : p[1];
	join_sprites(pl, tab[e_h] > tab[e_v] ? &p[0] : &p[1]);
	return (cos(x_rad) * (tab[e_h] < tab[e_v] ? tab[e_h] : tab[e_v]));
}