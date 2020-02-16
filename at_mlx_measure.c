#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

#include "at_mlx_measure.h"

# ifndef M_PI
 #define M_PI       3.14159265358979323846
# endif


// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
// http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53


double horizontal_intersection(t_player *pl, double sin, double cos, double tan)
{
	double 	y = sin > 0 ? (int)pl->player_y : (int)(pl->player_y + 1);
	double 	x = pl->player_x + (pl->player_y - y) / tan;
	double	y_a = sin > 0 ? -1 : 1;
	double	x_a = -1 * y_a / tan;
	int		ajusteur = sin > 0 ? -1 : 0;

	pl->wall_impact = 0;
	pl->wall_impact2 = 0;
	while (y < MAP_SIDE && y > 0 && x < MAP_SIDE && x > 0 && pl->map[(int)y + ajusteur][(int)x] == '0')
	{
		pl->wall_impact += x_a; 
		x += x_a;
		y += y_a;
	}
	//printf("pl->wall_impact : %f\n", pl->wall_impact);
	pl->wall_impact2 += fabs((pl->player_x - x) / cos) - pl->player_x; 
	pl->wall_orient = sin > 0 ? NORD_vert : SUD_rouge;
	return (fabs((pl->player_x - x) / cos)); // <-- distance entre le joueur et le mur
}

double vertical_intersection(t_player *pl, double cos, double tan)
{
	int 	x = cos < 0 ? (int)(pl->player_x): (int)(pl->player_x + 1);
	double 	y = pl->player_y + (pl->player_x - x) * tan;
	int 	x_a = cos < 0  ? -1 : 1;
	double	y_a = -1 * x_a * tan;
	int		ajusteur = cos < 0 ? -1 : 0;

	while (y < MAP_SIDE && y > 0 && x < MAP_SIDE && x > 0 && pl->map[(int)(y)][x + ajusteur] == '0')
	{
		x += x_a;
		y += y_a;
	}
	pl->wall_orient = cos < 0 ? OUEST_jaune : EST_bleu;
	return (fabs((pl->player_x - x) / cos));
}

double distance_incorrecte(t_player *pl)
{
	int V_orient, H_orient;
	double h_intersection = horizontal_intersection(pl, sin(pl->player_orient), cos(pl->player_orient), tan(pl->player_orient));
	H_orient = pl->wall_orient;
	double v_intersection = vertical_intersection(pl, cos(pl->player_orient), tan(pl->player_orient));
	V_orient = pl->wall_orient;
	pl->wall_orient = h_intersection < v_intersection ? H_orient : V_orient;
	return (h_intersection < v_intersection ? h_intersection : v_intersection);
}