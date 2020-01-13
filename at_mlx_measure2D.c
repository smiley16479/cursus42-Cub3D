#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include "essai.h"
#include "at_mlx_measure.h"
#include "at_mlx_render.h"
#include "at_mlx_hook.h"
#include "at_mlx_player_handler.h"
# ifndef M_PI
 #define M_PI       3.14159265358979323846
# endif

/* A virer apres l'essai */
// typedef struct s_struc {
// 	double	player_orient;
// 	double	player_orient_original;
// 	double	player_x;
// 	double	player_y;
// 	char	*map[5];
// }			t_data;


char map[MAP_SIDE][MAP_SIDE] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, 
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, 
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, 
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, 	
	{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1'}, 
	{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1'}, 
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, 
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, 
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, 
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

static inline double deg_to_rad(double degre)
{
	return (degre * M_PI / 180);
}
static inline double rad_to_deg(double rad)
{
	return (rad / (M_PI / 180));
}

// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
// http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53


double horizontal_intersection(t_data *su)
{
	double 	first_y_intersection = su->player_orient > 0 && su->player_orient < M_PI ? (int)(su->player_y): (int)(su->player_y + 1);
	double 	first_x_intersection = su->player_x + (su->player_y - first_y_intersection) / tan(su->player_orient);
	double	y_a = su->player_orient > 0 && su->player_orient < M_PI ? -1 : 1;
	double	x_a = -1 * y_a / tan(su->player_orient);
	int		ajusteur = /*su->player_orient  > M_PI / 4 && su->player_orient < 5 * M_PI / 4 */ su->player_orient > 0 && su->player_orient < M_PI ? -1 : 0;

	// printf("orient %.f, first_x_intersection : %.3f, first_y_intersection : %.3f, x_a %.3f, et y_a :%.3f\n",rad_to_deg(su->player_orient), first_x_intersection, first_y_intersection, x_a, y_a);
	while (first_y_intersection < MAP_SIDE && first_y_intersection > 0 && first_x_intersection < MAP_SIDE && first_x_intersection > 0 && su->map[(int)(first_y_intersection) + ajusteur/*+ y_a) * MAP_SIDE +*/] [(int)first_x_intersection /*+ (int)x_a)*/] == '0')
	{
		// printf("%c avec x,y : %f, %f\n", su->map[(int)(first_y_intersection)][(int)first_x_intersection], first_x_intersection, first_y_intersection);
		first_x_intersection += x_a;
		first_y_intersection += y_a;
	}
	// printf("orient %.f, wall_x_intersection : %.3f, %.3f, index de la map : %d , %d\n",rad_to_deg(su->player_orient), first_x_intersection, first_y_intersection, (int)first_x_intersection, (int)first_y_intersection);

//retour de la fonction dépends de la difference entre la position joueur et le mur
	return (fabs((su->player_x - first_x_intersection) / cos(su->player_orient))); // <-- distance entre le joueur et le mur
}

double vertical_intersection(t_data *su)
{
	int 	first_x_intersection = su->player_orient > M_PI / 2 && su->player_orient < 3 * M_PI / 2 ? (int)(su->player_x): (int)(su->player_x + 1);
	double 	first_y_intersection =   su->player_y + (su->player_x - first_x_intersection) * tan(su->player_orient);
	int 	x_a = su->player_orient > M_PI / 2 && su->player_orient < 3 * M_PI / 2 ? -1 : 1;
	double	y_a = -1 * x_a * tan(su->player_orient);
	int		ajusteur = su->player_orient > M_PI / 2 && su->player_orient < 3 * M_PI / 2 ? -1 : 0;

	// printf("orient %.f, first_x_intersection : %d, first_y_intersection : %.2f, x_a %d, et y_a :%f\n",rad_to_deg(su->player_orient), first_x_intersection, first_y_intersection, x_a, y_a);

	while (first_y_intersection < MAP_SIDE && first_y_intersection > 0 && first_x_intersection < MAP_SIDE && first_x_intersection > 0 && su->map[(int)(first_y_intersection) /* + y_a) * MAP_SIDE*/][first_x_intersection + ajusteur/*+ x_a*/] == '0')
	{
		// printf("first_x_intersection : %d , %f\n", first_x_intersection, first_y_intersection);
		first_x_intersection += x_a;
		first_y_intersection += y_a; 
	}
	// printf("su->player_x : %f, wall_y_intersection : %d, %.2f, index de la map : %d\n", su->player_x ,first_x_intersection, first_y_intersection, (int)((int)first_y_intersection * MAP_SIDE + first_x_intersection));
	return (fabs((su->player_x - first_x_intersection) / cos(su->player_orient)));
}


double distance_incorrecte(t_data *su)
{
	double h_intersection = horizontal_intersection(su);
	double v_intersection = vertical_intersection(su);
	return (h_intersection < v_intersection ? h_intersection : v_intersection);
}

void display_wall(t_data *su, int x, double distance)
{
	int		height;
	int		y;

	height = 277 / distance;
	// Dimensions de l’écran de projection = 320 x 200 (à vous de le choisir)
	// Centre de l’écran de projection = (160,100)
	// Distance entre la camera et l’écran de projection = 277
	// Angle entre deux rayons consécutifs = 60/320 degrés
	y  = 0;
	while(y < su->window_heigth)
		if (y >= su->window_heigth / 2 - (height / 2) && y < su->window_heigth / 2 + (height / 2))
			my_mlx_pixel_put(*su, x,  y++, 0x0000FF00);
		else
			my_mlx_pixel_put(*su, x,  y++, 0x00000000);
}


int main()
{
	t_data  *su;
	constructor_t_data(&su);
	*su = initializer_t_data(1000, 500);//(64 * map_side, 64 * map_side); // 1920, 1080,
	su->player_x = 5;
	su->player_y = 5;
	su->player_orient_origin = deg_to_rad(0);
	// su->player_orient = su->player_orient_original = deg_to_rad(0); // si tu mets -1 ds l'index du tab avec comme angle 225 les deux mesures sont bonnes

	for (int i = 0; i < MAP_SIDE; i++)
		su->map[i] = map[i];

	su->img = mlx_new_image(su->mlx, su->window_width, su->window_heigth);
	su->addr = mlx_get_data_addr(su->img, &(su->bits_per_pixel), &(su->line_length),
	&(su->endian));

	// printf("horizontal_intersection : %f\n\n",horizontal_intersection(&su));
	// printf("vertical_intersection 	: %f\n",vertical_intersection(&su));
	// printf("playerPos : (%.1f,%.1f) ; player_orient ; %f\n\n",su.player_x, su.player_y, su.player_orient);

	//Voici les hook pour les interuptions de touches
	// mlx_key_hook(su->mlx_win, close_window, su);
	// mlx_do_key_autorepeaton(su->mlx);
	mlx_hook(su->mlx_win, 2, 1L<<0, msg_keypressed_window, su);
	// mlx_hook(su->mlx_win, 3, 1L<<1, msg_keyreleased_window, su);

	// mlx_loop_hook(su->mlx, render_next_frame1, (void*)su);
	mlx_loop(su->mlx);
	return 0;
}

