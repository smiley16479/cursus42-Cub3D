/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_player_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:21:25 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/27 14:48:04 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "at_mlx_player_handler.h"

# ifndef M_PI
 #define M_PI       3.14159265358979323846
# endif

/*
int player_init_pos(void)
{
	char *str = "NSEW";
	int y = -1, x, i;
	while((x = -1) && ++y < 20)
		while((i = -1) && ++x < 20)
			while (str[++i])
				if (g_su->map[y * 20 + x] == str[i])
				{
					printf("player found on x : %d, y : %d oriented on :%c\n", x + 1, y + 1, str[i]);
					g_su->player_x = x + 0.5;
					g_su->player_y = y + 0.5;
					if (i == 0)
						g_su->player_orient = deg_to_rad(90);
					else if (i == 1)
						g_su->player_orient = deg_to_rad(270);
					else if (i == 2)
						g_su->player_orient = deg_to_rad(180);
					else if (i == 3)
						g_su->player_orient = deg_to_rad(360);
					return (y * 20 + x);
				}
	return (-1);
}*/

t_player *player_constructeur(t_player **to_return)
{
	if (!(*to_return = (t_player*)(malloc(sizeof(t_player)))))
		return (NULL); 
	return (*to_return);
}

t_player player_initializer(int player_x, int player_y, int deg)
{
	t_player	to_return;

	to_return.player_x = player_x + .5;
	to_return.player_y = player_y + .5;
	to_return.player_orient = 0;
	to_return.player_orient_origin = deg_to_rad(deg);
	// cst_tab_init(to_return.cst_tab);
	// if (!(to_return.key_tab = (int*)malloc(sizeof(int) * 250)))
		// return (to_return);
	// i = -1;
	// while (++i < 10)
		// (to_return.key_tab)[i] = 0;
	return (to_return);
}

int player_mov_hook(t_player *pl)
{
	player_mov(pl);
	player_rotate(pl);
	return(0);
}

void player_mov(t_player *pl/*, int keycode*/)
{	//up 13, down 1, left 0,right 2 (mac)
	float velocity = .05;
	double dir = pl->player_orient_origin;
	if (g_su->key_tab[w_key]/*keycode == 13 || keycode == 122*/) // up -> devant // seconde condition pour les keycode de linux
	{
		if (g_su->map[(int)(pl->player_y)][(int)(pl->player_x + cos(dir) * velocity)] == '0')
			pl->player_x += (cos(dir) * velocity);
		if (g_su->map[(int)(pl->player_y - sin(dir) * velocity)][(int)(pl->player_x)] == '0')
			pl->player_y -= (sin(dir) * velocity);
	}
	if (g_su->key_tab[s_key]/*keycode == 1 || keycode == 115*/) // down
	{
		if (g_su->map[(int)(pl->player_y)][(int)(pl->player_x - cos(dir) * velocity)] == '0')
			pl->player_x -= cos(dir) * velocity;
		if (g_su->map[(int)(pl->player_y + sin(dir) * velocity)][(int)(pl->player_x)] == '0')
			pl->player_y += sin(dir) * velocity;
	}
	if (g_su->key_tab[a_key]/*keycode == 0 || keycode == 113*/) // left
	{
		if (g_su->map[(int)(pl->player_y)][(int)(pl->player_x - sin(dir) * velocity)] == '0')
			pl->player_x -= sin(dir) * velocity;
		if (g_su->map[(int)(pl->player_y - cos(dir) * velocity)][(int)(pl->player_x)] == '0')
			pl->player_y -= cos(dir) * velocity;
	}
	if (g_su->key_tab[d_key]/*keycode == 2 || keycode == 100*/) // right
	{
		if (g_su->map[(int)(pl->player_y)][(int)(pl->player_x + sin(dir) * velocity)] == '0')
			pl->player_x += sin(dir) * velocity; 
		if (g_su->map[(int)(pl->player_y + cos(dir) * velocity)][(int)(pl->player_x)] == '0')
			pl->player_y += cos(dir) * velocity;
	}
}

void player_rotate(t_player *pl/*, int keycode*/)
{
	if ( g_su->key_tab[rightArrow_key]/*keycode == 123 || keycode == 65361*/) // left-arrow // seconde condition pour les keycode de linux
		pl->player_orient_origin += deg_to_rad(2);
	else if ( g_su->key_tab[leftArrow_key]/*keycode == 124 || keycode == 65363*/) // right-arrow
		pl->player_orient_origin -= deg_to_rad(2);
	//le probleme d'affichage vient de l'orientation... sans savoir encore pourquoi
	// if (((t_app*)su)->player_orient_origin >= 6.28)
		// ((t_app*)su)->player_orient_origin = 0.0;
	// else if (((t_app*)su)->player_orient_origin <= 0)
		// ((t_app*)su)->player_orient_origin =  6.28;
}

static inline void clearScreen(void)
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

/*
void wall_collision_checker(float x, float y)
{
	if (su->map[((int)y * MAP_SIDE + (int)x)] == '1')
		return ;
	else
	{
		su->player_y = y;
		su->player_x = x;
	}
}

int getchar_player_mov(void)
{
	char c = getchar();
	while (c != '\n')
	{
		write(1, &c, 1);
		if (c == 'z') // up
			wall_collision_checker(g_su, g_su->player_x, g_su->player_y - 0.1);
		else if (c == 'q') // left
			wall_collision_checker(g_su, g_su->player_x - 0.1, g_su->player_y);
		else if (c == 's') // down
			wall_collision_checker(g_su, g_su->player_x, g_su->player_y + 0.1);
		else if (c == 'd') // right
			wall_collision_checker(g_su, g_su->player_x + 0.1, g_su->player_y);
		else if (c == 'l') // left-arrow
		{
			g_su->player_orient += 0.09;
			if (g_su->player_orient > 2 * M_PI)
				g_su->player_orient = 0;
		}
		else if (c == 'm') // right-arrow
		{
			g_su->player_orient -= 0.09;
			if (g_su->player_orient < 0)
				g_su->player_orient = 2 * M_PI;
		}
		else
			return (0);
		c = getchar();
	}
	write(1, "\n", 1);
	return (1);
}

char get_player_pos(void)
{
	int x;

	x = 0;
	while (g_su->map[x])
	{
		char *str = "NSEW";
		while (*str)
			if (g_su->map[x] == *str++)
			{
				g_su->player_x = x % MAP_SIDE;
				g_su->player_y = x / MAP_SIDE;
				if (*(str - 1) == 'N')
					g_su->player_orient = deg_to_rad(90);
				else if (*(str - 1) == 'W')
					g_su->player_orient = deg_to_rad(180);
				else if (*(str - 1) == 'S')
					g_su->player_orient = deg_to_rad(270);
				else
					g_su->player_orient = deg_to_rad(0);
			}
		++x;
	}
	return (0);
}
*/

void display_player_orient(t_player *pl)
{
	// printf("player_orient : %f, M_PI * 3 / 4 (135): %f et M_PI * 5 / 4 (225): %f, 135 : %f, 270 : %f\n",su->player_orient, M_PI * 3 / 4 , M_PI * 5 / 4, deg_to_rad(135), deg_to_rad(270));
	if (pl->player_orient >= M_PI / 4 && pl->player_orient < M_PI * 3 / 4)
		write(1, "N", 1);
	else if (pl->player_orient >= M_PI * 3 / 4 && pl->player_orient < M_PI * 5 / 4)
		write(1, "W", 1);
	else if (pl->player_orient >= M_PI * 5 / 4 && pl->player_orient < M_PI * 7 / 4)
		write(1, "S", 1);
	else
		write(1, "E", 1);
}

void display_map(char *map[MAP_SIDE])
{
	int x;
	int y;

	y = 0;
	while (y < MAP_SIDE)
	{
		x = 0;
		while (x < MAP_SIDE)
		{
			if (!(x % 20))
				write(1, "\n", 1);
			else
				write(1, " ", 1);
			if (map[y][x] == '1')
				write(1, "1", 1);
			// else if (x == ((int)g_su->player_y * MAP_SIDE + (int)g_su->player_x)/*(c = is_player_here(g_su, x))*/)
				// display_player_orient(g_su);
			else
				write(1, "0", 1);
			++x;
		}
		++y;
	}			
	write(1, "\n\n", 2);
}