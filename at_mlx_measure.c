#include <math.h>
#include "essai.h"
#include "at_mlx_measure.h"

int player_init_pos(t_data *su)
{
	char *str = "NSEW";
	int y = -1, x, i;
	while((x = -1) && ++y < 20)
		while((i = -1) && ++x < 20)
			while (str[++i])
				if (su->map[y * 20 + x] == str[i])
				{
					printf("player found on x : %d, y : %d oriented on :%c\n", x + 1, y + 1, str[i]);
					su->player_x = x + 0.5;
					su->player_y = y + 0.5;
					if (i == 0) // il va surement falloir redefinir ça en gradian
						su->player_orient = 100; //M_PI / 2; // en gradian 100
					else if (i == 1)
						su->player_orient = 300; //3 * M_PI / 2; //300
					else if (i == 2)
						su->player_orient = 200; //M_PI; // 200
					else if (i == 3)
						su->player_orient = 0; //2* M_PI; // 0 ou 400... "gon" <- unite
					return (y * 20 + x);
				}
	return (-1);
}

int player_mov(t_data *su, int keycode)
{
	if (keycode == 13) // up
		su->player_y -= 0.02;
	else if (keycode == 0) // left
		su->player_x -= 0.02;
	else if (keycode == 1) // down
		su->player_y += 0.02;
	else if (keycode == 2) // right
		su->player_x += 0.02;
	return (0);
}

int player_rotate(t_data *su, int keycode)
{
	if (keycode == 13) // left-arrow
		su->player_orient += 0.9;
	else if (keycode == 0) // right-arrow
		su->player_orient -= 0.9;
}
// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
int measure_y(t_data *su)
{
	int player_rx;
	int player_ry;
	double y_a;
	player_rx = (int)su->player_x;
	player_ry = (int)su->player_y;
	if (su->player_orient > 0 && su->player_orient < 50)
		y_a = tan(su->player_orient) ;
	if (su->player_orient > 50 && su->player_orient < 100)
		y_a = sin(su->player_orient) ;
	else if (su->player_orient > 350)
			;
	return (0);
}

int measure_x(t_data *su)
{
	int player_rx;
	int player_ry;
	double x_a;
	player_rx = (int)su->player_x;
	player_ry = (int)su->player_y;
	if (su->player_orient > 0 && su->player_orient < 50)
		x_a = 1 / tan(su->player_orient) ;
	else if (su->player_orient > 350)
			;
	return (0);
}