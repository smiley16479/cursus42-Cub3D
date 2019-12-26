#include <math.h>
#include <stdio.h>
// #include "essai.h"
// #include "at_mlx_measure.h"
// #define M_PI       3.14159265358979323846


/* A virer apres l'essai */
typedef struct s_struc {
	double player_orient;
	double player_x;
	double player_y;
	int * map;
}			t_data;

static inline double deg_to_rad(double degre)
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
					if (i == 0)
						su->player_orient = deg_to_rad(90);
					else if (i == 1)
						su->player_orient = deg_to_rad(270);
					else if (i == 2)
						su->player_orient = deg_to_rad(180);
					else if (i == 3)
						su->player_orient = deg_to_rad(360);
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

double measure_x(t_data *su)
{
	/*
		** p_o == player_orientation en radian**
		degree 0 to radian 0.000000
		degree 90 to radian 1.570796
		degree 180 to radian 3.141593
		degree 270 to radian 4.712389
		degree 360 to radian 6.283185
	*/
	if (su->player_orient > 0 && su->player_orient < 1.570796)
		"?";

/*
	if (p_o != 0 && p_o != 1.570796 && p_o != 3.141593
		&& p_o != 4.712389 && p_o != 6.283185)
		return (cos(p_o));
	else if (p_o == 3.141593)
		return (-1);
	else
		return (p_o == 6.283185 || p_o == 0 ? 1 : 0);*/
}

double measure_y(t_data *su)
{



	/*
	if (p_o != 0 && p_o != 1.570796 && p_o != 3.141593
		&& p_o != 4.712389 && p_o != 6.283185)
		return (sin(p_o) * -1);
	else if (p_o == 1.570796)
		return (-1);
	else
		return (p_o == 4.712389 ? 1 : 0);
	*/
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
	su.player_orient = 0;
	printf("degree 0 to radian %f\n", deg_to_rad(0));
	printf("degree 90 to radian %f\n", deg_to_rad(90));
	printf("degree 180 to radian %f\n", deg_to_rad(180));
	printf("degree 270 to radian %f\n", deg_to_rad(270));
	printf("degree 360 to radian %f\n", deg_to_rad(360));
	int i = 0;
	while (i <= 360)
		printf("%f\n",measure_x(&su)), su.player_orient = deg_to_rad(i += 45);
}

