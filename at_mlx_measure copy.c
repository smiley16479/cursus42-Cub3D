#include <math.h>
#include <stdio.h>
#include <unistd.h>
// #include "essai.h"
// #include "at_mlx_measure.h"
# ifndef M_PI
 #define M_PI       3.14159265358979323846
# endif

#define MAP_SIDE 10


/* A virer apres l'essai */
typedef struct s_struc {
	double player_orient;
	double player_orient_original;
	double player_x;
	double player_y;
	char * map;
}			t_data;


char map[400] = {
	'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 
	'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', 
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
		su->player_orient += 0.09;
	else if (keycode == 0) // right-arrow
		su->player_orient -= 0.09;
}

static inline void clearScreen(void)
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void wall_collision_checker(t_data *su, float x, float y)
{
	if (su->map[((int)y * MAP_SIDE + (int)x)] == '1')
		return ;
	else
	{
		su->player_y = y;
		su->player_x = x;
	}
}

int getchar_player_mov(t_data *su)
{
	char c = getchar();
	while (c != '\n')
	{
		write(1, &c, 1);
		if (c == 'z') // up
			wall_collision_checker(su, su->player_x, su->player_y - 0.1);
		else if (c == 'q') // left
			wall_collision_checker(su, su->player_x - 0.1, su->player_y);
		else if (c == 's') // down
			wall_collision_checker(su, su->player_x, su->player_y + 0.1);
		else if (c == 'd') // right
			wall_collision_checker(su, su->player_x + 0.1, su->player_y);
		else if (c == 'l') // left-arrow
		{
			su->player_orient += 0.09;
			if (su->player_orient > 2 * M_PI)
				su->player_orient = 0;
		}
		else if (c == 'm') // right-arrow
		{
			su->player_orient -= 0.09;
			if (su->player_orient < 0)
				su->player_orient = 2 * M_PI;
		}
		else
			return (0);
		c = getchar();
	}
	write(1, "\n", 1);
	return (1);
}

char get_player_pos(t_data *su)
{
	int x;

	x = 0;
	while (su->map[x])
	{
		char *str = "NSEW";
		while (*str)
			if (su->map[x] == *str++)
			{
				su->player_x = x % MAP_SIDE;
				su->player_y = x / MAP_SIDE;
				if (*(str - 1) == 'N')
					su->player_orient = deg_to_rad(90);
				else if (*(str - 1) == 'W')
					su->player_orient = deg_to_rad(180);
				else if (*(str - 1) == 'S')
					su->player_orient = deg_to_rad(270);
				else
					su->player_orient = deg_to_rad(0);
			}
		++x;
	}
	return (0);
}

void display_player_orient(t_data *su)
{
	// printf("player_orient : %f, M_PI * 3 / 4 (135): %f et M_PI * 5 / 4 (225): %f, 135 : %f, 270 : %f\n",su->player_orient, M_PI * 3 / 4 , M_PI * 5 / 4, deg_to_rad(135), deg_to_rad(270));
	if (su->player_orient >= M_PI / 4 && su->player_orient < M_PI * 3 / 4)
		write(1, "N", 1);
	else if (su->player_orient >= M_PI * 3 / 4 && su->player_orient < M_PI * 5 / 4)
		write(1, "W", 1);
	else if (su->player_orient >= M_PI * 5 / 4 && su->player_orient < M_PI * 7 / 4)
		write(1, "S", 1);
	else
		write(1, "E", 1);
}


void display_map(char *map, t_data *su)
{
	int x = 0;

	while (x < 400)
	{
		if (!(x % 20))
			write(1, "\n", 1);
		else
			write(1, " ", 1);
		if (map[x] == '1')
			write(1, "1", 1);
		else if (x == ((int)su->player_y * MAP_SIDE + (int)su->player_x)/*(c = is_player_here(su, x))*/)
			display_player_orient(su);
		else
			write(1, "0", 1);
		++x;
	}	
	write(1, "\n\n", 2);
}
// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
// http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#53


double horizontal_intersection(t_data *su)
{
	int 	first_y_intersection = su->player_orient > 0 && su->player_orient < M_PI ? (int)(su->player_y - 1): (int)(su->player_y + 1);
	double 	first_x_intersection = su->player_x + (su->player_y - first_y_intersection) / tan(su->player_orient);
	int 	y_a = su->player_orient > 0 && su->player_orient < M_PI ? -1 : 1;
	double	x_a = -1 * y_a / tan(su->player_orient);

	// printf("orient %.f, first_x_intersection : %.1f, first_y_intersection : %d, x_a %.1f, et y_a :%d\n",rad_to_deg(su->player_orient), first_x_intersection, first_y_intersection, x_a, y_a);
	while (su->map[(int)((first_y_intersection + y_a) * MAP_SIDE + first_x_intersection +  x_a)] == '0')
	{
		// printf("%c\n", su->map[(int)(first_y_intersection * MAP_SIDE + first_x_intersection)]);
		first_x_intersection += x_a;
		first_y_intersection += y_a;
	}
	// printf("wall_x_intersection : %.1f, %d, index de la map : %d\n",first_x_intersection, first_y_intersection, (int)(first_y_intersection * MAP_SIDE + (int)first_x_intersection));

//retour de la fonction dépends de la difference entre la position joueur et le mur
	// if (su->player_orient > M_PI / 2 && su->player_orient < 3 * M_PI / 2)
		return (fabs((su->player_x - first_x_intersection) / cos(su->player_orient))); // <-- distance entre le joueur et le mur
	// else
		// return (fabs((first_x_intersection - su->player_x) / cos(su->player_orient))); // <-- distance entre le joueur et le mur
}

double vertical_intersection(t_data *su)
{
	int 	first_x_intersection = su->player_orient > M_PI / 2 && su->player_orient < 3 * M_PI / 2 ? (int)(su->player_x - 1): (int)(su->player_x + 1);
	double 	first_y_intersection =   su->player_y + (su->player_x - first_x_intersection) * tan(su->player_orient);
	int 	x_a = su->player_orient > M_PI / 2 && su->player_orient < 3 * M_PI / 2 ? -1 : 1;
	double	y_a = -1 * x_a * tan(su->player_orient);

	// printf("orient %.f, first_x_intersection : %d, first_y_intersection : %.1f, x_a %d, et y_a :%.1f\n",rad_to_deg(su->player_orient), first_x_intersection, first_y_intersection, x_a, y_a);
	while (su->map[(int)((first_y_intersection + y_a) * MAP_SIDE + first_x_intersection +  x_a)] == '0')
	{
		first_x_intersection += x_a;
		first_y_intersection += y_a; 
	}
	// printf("wall_y_intersection : %d, %.1f, index de la map : %d\n",first_x_intersection, first_y_intersection, (int)((int)first_y_intersection * 20 + first_x_intersection));
	return (fabs((su->player_x - first_x_intersection) / cos(su->player_orient)));
}


double distance_incorrecte(t_data *su)
{
	double h_intersection = horizontal_intersection(su);
	double v_intersection = vertical_intersection(su);
	return (h_intersection < v_intersection ? h_intersection : v_intersection);
}


int main()
{
	t_data su;
	su.player_x = 2;
	su.player_y = 2;
	su.player_orient = su.player_orient_original = deg_to_rad(315); // si tu mets -1 ds l'index du tab avec comme angle 225 les deux mesures sont bonnes
	su.map = map;

	// Pour prendre la position du joueur depuis la map[400]
	// get_player_pos(&su);
	// printf("playerPos : (%.1f,%.1f)\n",su.player_x, su.player_y);

/*
	char boo = 1;
	while (boo)
	{
		display_map(map, &su);
		boo = getchar_player_mov(&su);
		clearScreen();

	}
*/
	printf("playerPos : (%.1f,%.1f) ; player_orient ; %f\n\n",su.player_x, su.player_y, su.player_orient);
	printf("horizontal_intersection : %f\n\n",horizontal_intersection(&su));
	printf("vertical_intersection 	: %f\n",vertical_intersection(&su));

	int x = -30;
	double x_rad;
	double d_incorrecte, d_correcte;
	printf("radian -30 : %f\n", deg_to_rad(x));
	while (x < 30)
	{
		su.player_orient = su.player_orient_original + (x_rad = deg_to_rad(x));
		// printf("su.player_orient : %f\n", su.player_orient);
		d_incorrecte = distance_incorrecte(&su);
		// printf("d_correcte	: %f\n",d_correcte = d_incorrecte * cos(x_rad));
		printf("d_incorrecte	: %f\n", d_incorrecte);
		++x;
	}

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

