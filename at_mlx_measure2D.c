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

#define t_height 100

char map[MAP_SIDE][MAP_SIDE] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, 
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, 
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '1'}, 
	{'1', '0', '0', '1', '0', '0', '1', '0', '0', '1'}, 	
	{'1', '0', '0', '0', '0', '0', '1', '0', '1', '1'}, 
	{'1', '0', '0', '0', '0', '0', '1', '0', '1', '1'}, 
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '1'}, 
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, 
	{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'}, 
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


double horizontal_intersection(t_data *su, double sin, double cos, double tan)
{
	double 	y = sin > 0 ? (int)(su->player_y): (int)(su->player_y + 1);
	double 	x = su->player_x + (su->player_y - y) / tan;
	double	y_a = sin > 0 ? -1 : 1;
	double	x_a = -1 * y_a / tan;
	int		ajusteur = sin > 0 ? -1 : 0;

	while (y < MAP_SIDE && y > 0 && x < MAP_SIDE && x > 0 && su->map[(int)(y) + ajusteur][(int)x] == '0')
	{
		x += x_a;
		y += y_a;
	}
	su->wall_orient = sin > 0 ? NORD_vert : SUD_rouge;
	return (fabs((su->player_x - x) / cos)); // <-- distance entre le joueur et le mur
}

double vertical_intersection(t_data *su, double cos, double tan)
{
	int 	x = cos < 0 ? (int)(su->player_x): (int)(su->player_x + 1);
	double 	y = su->player_y + (su->player_x - x) * tan;
	int 	x_a = cos < 0  ? -1 : 1;
	double	y_a = -1 * x_a * tan;
	int		ajusteur = cos < 0 ? -1 : 0;

	while (y < MAP_SIDE && y > 0 && x < MAP_SIDE && x > 0 && su->map[(int)(y)][x + ajusteur] == '0')
	{
		x += x_a;
		y += y_a;
	}
	su->wall_orient = cos < 0 ? OUEST_jaune : EST_bleu;
	return (fabs((su->player_x - x) / cos));
}

double distance_incorrecte(t_data *su)
{
	int V_orient, H_orient;
	double h_intersection = horizontal_intersection(su, sin(su->player_orient), cos(su->player_orient), tan(su->player_orient));
	H_orient = su->wall_orient;
	double v_intersection = vertical_intersection(su, cos(su->player_orient), tan(su->player_orient));
	V_orient = su->wall_orient;
	su->wall_orient = h_intersection < v_intersection ? H_orient : V_orient;
	return (h_intersection < v_intersection ? h_intersection : v_intersection);
}

void display_wall(t_data *su, int x, double distance)
{
	int		height;
	int		y;
	int		color_tab[4] = {0x00FF0000, 0x0000FF00, 0x000000FF, 0x00f5f242};

	height = 277 / distance;
	// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/03-projection
	// Dimensions de l’écran de projection = 320 x 200 (à vous de le choisir)
	// Centre de l’écran de projection = (160,100)
	// Distance entre la camera et l’écran de projection = 277
	// Angle entre deux rayons consécutifs = 60/320 degrés
	y  = 0;
	while(y < su->window_heigth)
		if (y >= su->window_heigth / 2 - (height / 2) && y < su->window_heigth / 2 + (height / 2))
			my_mlx_pixel_put(*su, x,  y++, color_tab[su->wall_orient]);
		else
			my_mlx_pixel_put(*su, x,  y++, 0x00000000);
}

void display_textured_wall(t_data *su, int x, double distance)
{
	int		height;
	int		y;
	double	step;

	height = 277 / distance;
	step = t_height / height;
	y  = 0;
	while(y < su->window_heigth)
		if (y >= su->window_heigth / 2 - (height / 2) && y < su->window_heigth / 2 + (height / 2))
		{
			my_mlx_pixel_put(*su, x, y, ((t_textu_data*)su->text)->text_tab[0]
			[((y % ((t_textu_data*)su->text)->text_height) * ((t_textu_data*)su->text)->text_line_length + (x % ((t_textu_data*)su->text)->text_width) * (((t_textu_data*)su->text)->text_bits_per_pixel / 8))]);
			++y;
		}
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

	for (int i = 0; i < MAP_SIDE; i++)
		su->map[i] = map[i];
	display_map(su->map,su);
	printf("player_orient : %.2f (ds le main l131)\n", su->player_orient_origin);
	
	su->img = mlx_new_image(su->mlx, su->window_width, su->window_heigth);
	su->addr = mlx_get_data_addr(su->img, &(su->bits_per_pixel), &(su->line_length),&(su->endian));

	t_textu_data t_su;
    char    *relative_path = "texture/brick.xpm";
	t_su.text = mlx_xpm_file_to_image(su->mlx, relative_path, &(t_su.text_width), &(t_su.text_height));
	t_su.text_tab[0] = mlx_get_data_addr(t_su.text, &(t_su.text_bits_per_pixel), &(t_su.text_line_length),&(t_su.endian));

	su->text = &t_su;

	//Voici les hook pour les interuptions de touches
	// mlx_key_hook(su->mlx_win, close_window, su);
	// mlx_do_key_autorepeaton(su->mlx);
	mlx_hook(su->mlx_win, 2, 1L<<0, msg_keypressed_window, su);
	// mlx_hook(su->mlx_win, 3, 1L<<1, msg_keyreleased_window, su);

	mlx_loop_hook(su->mlx, render_next_frame1, (void*)su);
	mlx_loop(su->mlx);
	return 0;
}