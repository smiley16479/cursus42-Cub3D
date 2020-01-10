#include <math.h>
#include <stdio.h>
// #include "essai.h"
// #include "at_mlx_measure.h"
# ifndef M_PI
 #define M_PI       3.14159265358979323846
# endif

/* A virer apres l'essai */
typedef struct s_struc {
	double player_orient;
	double player_x;
	double player_y;
	int * map;
}			t_data;

static inline double deg_to_rad(double degre)
{
	return (degre * M_PI / 180.);
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
// http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53

double first_x_intersection(t_data *su)
{
	int 	first_y_intersection = su->player_orient > 0 && su->player_orient < M_PI ? (int)su->player_y : (int)su->player_y + 1;
	double 	first_x_intersection = su->player_x + (su->player_y - first_y_intersection) / tan(su->player_orient);
	int 	y_a = su->player_orient > 0 && su->player_orient < M_PI ? -1 : 1;
	double	x_a = 1 / tan(su->player_orient);

	printf("first_x_intersection : %f, first_y_intersection : %d, \net x_a %f, et y_a :%d\n\n",first_x_intersection, first_y_intersection, x_a, y_a);
	// while (su->map[y_a * 20 + (int)x_a] == 0)
	while (su->map[first_y_intersection * 20 + (int)first_x_intersection] == 0)
	{
		first_y_intersection += y_a; 
		first_x_intersection += x_a;
	}
	printf("first_x_intersection : %f, first_y_intersection : %d, \net x_a %f, et y_a :%d\n",first_x_intersection, first_y_intersection, x_a, y_a);
	return (fabs((su->player_x - first_x_intersection) / cos(su->player_orient)));
/*
	if (su->player_orient > 0 && su->player_orient < M_PI)
		if (su->player_orient != 0 && su->player_orient != M_PI / 2 && su->player_orient != M_PI
			&& su->player_orient != 3 * M_PI / 2 && su->player_orient != 2 * M_PI)
			return (su->player_x + ((su->player_y - (int)su->player_y) / tan(su->player_orient)));
	else if (su->player_orient < M_PI && su->player_orient < 2 * M_PI)
			return (su->player_x + ((su->player_y - (int)su->player_y) / tan(su->player_orient)));

	else if (su->player_orient == M_PI /2 || su->player_orient == 3 * M_PI / 2)
		return (su->player_x);
	else 
		return (su->player_orient ==  0 ? (int)su->player_x + 1 : (int)su->player_x);
*/
}

double first_y_intersection(t_data *su)
{
	if (su->player_orient != 0 && su->player_orient != M_PI / 2 && su->player_orient != M_PI
		&& su->player_orient != 3 * M_PI / 2 && su->player_orient != 2 * M_PI)
		return (su->player_y + ((su->player_x - (int)su->player_x) * tan(su->player_orient)));
	// if (su->player_orient > 0 && su->player_orient < M_PI / 2)
		// return (su->player_y + ((su->player_x - (int)su->player_x) * tan(su->player_orient)));
	// else if (su->player_orient > M_PI / 2 && su->player_orient < M_PI)
		// return (su->player_y + ((su->player_x - (int)su->player_x) / tan(su->player_orient)));
	// else if (su->player_orient > M_PI && su->player_orient < 3 * M_PI / 2)
		// return (su->player_y + ((su->player_x - (int)su->player_x) / tan(su->player_orient)));
	// else if (su->player_orient > 3 * M_PI / 2 && su->player_orient < 2 * M_PI)
		// return (su->player_y + ((su->player_x - (int)su->player_x) / tan(su->player_orient)));
	else if (su->player_orient == 0 || su->player_orient == M_PI || su->player_orient == 2 * M_PI)
		return (su->player_y);
	else 
		return (su->player_orient ==  M_PI / 2 ? (int)su->player_y : (int)su->player_y + 1);
}

double measure_x(t_data *su)
{
	/*
		** p_o == player_orientation en radian**
		degree 0 to radian 0.000000   == 0
		degree 90 to radian 1.570796  == π/2
		degree 180 to radian 3.141593 == π
		degree 270 to radian 4.712389 == 3 * π/2
		degree 360 to radian 6.283185 == 2π
	*/

		printf("orient :%f\n", su->player_orient);
	//distance parcouru en x entre la positon du joueur et la 1ere intersection avec les horizontales



	if (su->player_orient > 0 && su->player_orient < 1.570796)
		return (1 / tan(su->player_orient));
	else if (su->player_orient > 1.570796 && su->player_orient < 3.141593)
		return (1 / tan(su->player_orient));
	else if (su->player_orient > 3.141593 && su->player_orient < 4.712389)
		return (1 / tan(su->player_orient));
	else if (su->player_orient > 4.712389 && su->player_orient < 6.283185)
		return (1 / tan(su->player_orient) * - 1);


/*
	if (p_o != 0 && p_o != 1.570796 && p_o != 3.141593
		&& p_o != 4.712389 && p_o != 6.283185)
		return (cos(p_o));
	else if (p_o == 3.141593)
		return (-1);
	else
		return (p_o == 6.283185 || p_o == 0 ? 1 : 0);*/
	return 0;//to remove
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
	return 0;//to remove
}

int is_a_wall(t_data *su, double y_offset, double x_offset)
{
	// if ("I hit a wall")
		// "do smth";
	return (0);
}

int main()
{
	int map[400] = {
		1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 
		1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
	};

	t_data su;
	su.player_x = 1;
	su.player_y = 2.2;
	su.map = map;
	int x = 0;
	su.player_orient = deg_to_rad(x += 45);

	printf("%f\n",first_x_intersection(&su));

	/*
	printf("pour x : %f, et y : %f\n", su.player_x, su.player_y);
	while (x <= 360)
	{
		printf("first intersection pour orient %3d: (%f, %f)\n", x, first_x_intersection(&su), first_y_intersection(&su));
		su.player_orient = deg_to_rad(x += 45);
	}*/
	// printf("degree 180 to radian %f\n", deg_to_rad(180));
	// while (i <= 360)
	// su.player_orient = deg_to_rad(20);
		// printf("%f\n",measure_x(&su));
		// printf("%f\n",measure_x(&su));
		// printf("%f\n",measure_x(&su));
		// printf("%f\n",measure_x(&su));
}

