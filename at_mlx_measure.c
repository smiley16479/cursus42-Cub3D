#include <math.h>
#include <stdio.h>
// #include "essai.h"
// #include "at_mlx_measure.h"
#define M_PI       3.14159265358979323846


/* A virer apres l'essai */
typedef struct s_struc {
	double player_orient;
	double player_x;
	double player_y;
	int * map;
}			t_data;

double deg_to_rad(double degre)
{
	return (degre * M_PI / 180);
}

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

void player_mov(t_data *su, int keycode)
{
	if (keycode == 13) // up
		su->player_y -= 0.02;
	else if (keycode == 0) // left
		su->player_x -= 0.02;
	else if (keycode == 1) // down
		su->player_y += 0.02;
	else if (keycode == 2) // right
		su->player_x += 0.02;
}

void player_rotate(t_data *su, int keycode)
{
	if (keycode == 13) // left-arrow
		su->player_orient += 0.9;
	else if (keycode == 0) // right-arrow
		su->player_orient -= 0.9;
}
// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
double measure_y(t_data *su)
{
	double y_a;

	if (su->player_orient > 0 && su->player_orient < 100)
		y_a = tan(su->player_orient) * -1;
	else if (su->player_orient > 100 && su->player_orient < 200)
		y_a = tan(su->player_orient);
	else if (su->player_orient > 200 && su->player_orient < 300)
		y_a = tan(su->player_orient);
	else if (su->player_orient > 300 && su->player_orient < 400)
		y_a = tan(su->player_orient) * -1;
	else if (su->player_orient == 100)
		y_a = -1;
	else if (su->player_orient == 300)
		y_a = 1;
	else
		y_a = 0;
	return (y_a);
}

double measure_x(t_data *su)
{
	double x_a;

	if (su->player_orient > 0 && su->player_orient < 100)
		x_a = tan(su->player_orient);//, printf("su->player_orient : %f\n", su->player_orient);
	//	x_a = 1 / tan(su->player_orient), printf("su->player_orient : %f\n", su->player_orient);
	else if (su->player_orient > 100 && su->player_orient < 200)
		x_a = 1 / tan(su->player_orient);
	else if (su->player_orient > 200 && su->player_orient < 300)
		x_a = 1 / tan(su->player_orient) * -1;
	else if (su->player_orient > 300 && su->player_orient < 400)
		x_a = 1 / tan(su->player_orient) * -1;
	else if (su->player_orient == 0 || su->player_orient == 400)
		x_a = 1;
	else if (su->player_orient == 200)
		x_a = -1;
	else
		x_a = 0;
	return (x_a);
}

int is_a_wall(t_data *su, double y_offset, double x_offset)
{
	// if ("I hit a wall")
		// "do smth";
	return (0);
}

int main()
{
	t_data su;
	su.player_orient = 0.785398163;
	printf("degree 45 to radian %f\n", deg_to_rad(45));
	printf("%f\n",measure_x(&su));
}

