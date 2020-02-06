/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_player_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:21:25 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/06 16:47:50 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
#include "struc.h"
#include "angle_convert.h"
# ifndef M_PI
 #define M_PI       3.14159265358979323846
# endif

/*
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
}*/

void player_mov(t_data *su, int keycode)
{
	double velocity = .2;
	double dir = su->player_orient_origin;
	if (keycode == 13) // up -> devant
	{
		if (su->map[(int)(su->player_y)][(int)(su->player_x + (cos(dir)) * velocity)] == '0')
			su->player_x += (cos(dir) * velocity);
		if (su->map[(int)(su->player_y - sin(dir) * velocity)][(int)(su->player_x)] == '0')
			su->player_y -= (sin(dir) * velocity);
	}
	else if (keycode == 1) // down
	{
		if (su->map[(int)(su->player_y)][(int)(su->player_x - cos(dir) * velocity)] == '0')
			su->player_x -= cos(dir) * velocity;
		if (su->map[(int)(su->player_y + sin(dir) * velocity)][(int)(su->player_x)] == '0')
			su->player_y += sin(dir) * velocity;
	}
	else if (keycode == 0) // left
	{
		if (su->map[(int)(su->player_y)][(int)(su->player_x - sin(dir) * velocity)] == '0')	
			su->player_x -= sin(dir) * velocity;
		if (su->map[(int)(su->player_y - cos(dir) * velocity)][(int)(su->player_x)] == '0')	
			su->player_y -= cos(dir) * velocity;
	}
	else if (keycode == 2) // right
	{
		if (su->map[(int)(su->player_y)][(int)(su->player_x + sin(dir) * velocity)] == '0')	
			su->player_x += sin(dir) * velocity; 
		if (su->map[(int)(su->player_y + cos(dir) * velocity)][(int)(su->player_x)] == '0')	
			su->player_y += cos(dir) * velocity;
	}	
}

void player_rotate(t_data *su, int keycode)
{
	if (keycode == 123) // left-arrow
		su->player_orient_origin += deg_to_rad(3);
	else if (keycode == 124) // right-arrow
		su->player_orient_origin -= deg_to_rad(3);
	
	//le probleme d'affichage vient de l'orientation... sans savoir encore pourquoi
	// if (((t_data*)su)->player_orient_origin >= 6.28)
		// ((t_data*)su)->player_orient_origin = 0.0;
	// else if (((t_data*)su)->player_orient_origin <= 0)
		// ((t_data*)su)->player_orient_origin =  6.28;
}

static inline void clearScreen(void)
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

/*
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
*/

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

void display_map(char *map[MAP_SIDE], t_data *su)
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
			// else if (x == ((int)su->player_y * MAP_SIDE + (int)su->player_x)/*(c = is_player_here(su, x))*/)
				// display_player_orient(su);
			else
				write(1, "0", 1);
			++x;
		}
		++y;
	}			
	write(1, "\n\n", 2);
}