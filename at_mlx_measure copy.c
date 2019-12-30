#include <math.h>
#include <stdio.h>
#include <unistd.h>
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
	char * map;
}			t_data;



char map[401] = {
	'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', 
};


static inline double deg_to_rad(double degre)
{
	return (degre * M_PI / 180);
}
static inline double rad_to_deg(double rad)
{
	return (rad / (M_PI / 180));
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

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

int getchar_player_mov(t_data *su)
{
	char c = getchar();
	while (c != '\n')
	{
		write(1, &c, 1);
		if (c == 'z') // up
			su->player_y -= 0.1;
		else if (c == 'q') // left
			su->player_x -= 0.1;
		else if (c == 's') // down
			su->player_y += 0.1;
		else if (c == 'd') // right
			su->player_x += 0.1;
		else if (c == 'l') // left-arrow
			su->player_orient += 0.9;
		else if (c == 'm') // right-arrow
			su->player_orient -= 0.9;
		else
			return (0);
		c = getchar();
	}
	write(1, "\n", 1);
	return (1);
}

char is_player_here(t_data *su, int x)
{
	int y = 64 * x + 64;
	while (x < y)
	{
		char *str = "NSEW";
		while (*str)
			if (su->int_map[x] == *str++)
				return (--*str);
		++x;
	}

}

void display_map(char *map, t_data *su)
{
	int x = -1;
	char c = 0;

	while (map[++x])
	{
		if (!(x % 20))
			write(1, "\n", 1);
		else
			write(1, " ", 1);
		if ((c = is_player_here(su, x)))
			write(1, &c, 1);
		else
			write(1, &map[x], 1);
	}	
	write(1, "\n\n", 2);
}
// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
// http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53

double horizontal_first_intersection(t_data *su)
{

}

double horizontal_intersection(t_data *su)
{
	int 	first_y_intersection = su->player_orient > 0 && su->player_orient < M_PI ? 
			(int)su->player_y : (int)su->player_y + 1;

	double 	first_x_intersection = su->player_x + (su->player_y - first_y_intersection) / tan(su->player_orient);

	int 	y_a = su->player_orient > 0 && su->player_orient < M_PI ? -1 : 1;
	double	x_a = 1 / tan(su->player_orient);

	printf("orient %.f, first_x_intersection : %f, first_y_intersection : %d, et x_a %f, et y_a :%d\n\n",rad_to_deg(su->player_orient), first_x_intersection, first_y_intersection, x_a, y_a);
	// while (su->map[y_a * 20 + (int)x_a] == 0)
	while (su->map[first_y_intersection * 20 + (int)first_x_intersection] == 0)
	{
		first_y_intersection += y_a;
		first_x_intersection += x_a;
	}
	// printf("wall_x_intersection : %f, wall_y_intersection : %d, index de la map : %d\n",first_x_intersection, first_y_intersection, first_y_intersection * 20 + (int)first_x_intersection);
	return (fabs((su->player_x - first_x_intersection) / cos(su->player_orient)));
}

double vertical_first_intersection(t_data *su)
{

}

double vertical_intersection(t_data *su)
{
	int 	first_x_intersection = su->player_orient > M_PI / 2 && su->player_orient < 3 * M_PI / 2 ? 
			(int)su->player_x : (int)su->player_x + 1;

	double 	first_y_intersection = su->player_y + (su->player_x - first_x_intersection) * tan(su->player_orient);
	int 	x_a = su->player_orient > M_PI / 2 && su->player_orient < 3 * M_PI / 2 ? -1 : 1;
	double	y_a = tan(su->player_orient);
	// printf("first_x_intersection : %f, first_y_intersection : %d, et x_a %f, et y_a :%d\n\n",first_x_intersection, first_y_intersection, x_a, y_a);
	// while (su->map[y_a * 20 + (int)x_a] == 0)
	while (su->map[(int)first_y_intersection * 20 + first_x_intersection] == 0)
	{
		first_y_intersection += y_a; 
		first_x_intersection += x_a;
	}
	// printf("wall_x_intersection : %f, wall_y_intersection : %d, index de la map : %d\n",first_x_intersection, first_y_intersection, first_y_intersection * 20 + (int)first_x_intersection);
	return (fabs((su->player_x - first_x_intersection) / cos(su->player_orient)));
}

int main()
{
	map[400] = 10;
	t_data su;
	su.player_x = 1.5;
	su.player_y = 1.5;
	su.player_orient = deg_to_rad(179);
	su.map = map;
	int x = 0;

	char boo = 1;
	while (boo)
	{



		display_map(map);
		boo = getchar_player_mov(&su);
		clearScreen();

	}

	// printf("playerPos : (%.1f,%.1f)\n",su.player_x, su.player_y);
	// printf("%f\n",horizontal_intersection(&su));
	// printf("%f\n",vertical_intersection(&su));

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
		return 0;
}

