/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_player_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:21:25 by adtheus           #+#    #+#             */
/*   Updated: 2020/03/12 16:47:47 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "at_mlx_player_handler.h"

# ifndef M_PI
 #define M_PI       3.14159265358979323846
# endif

t_player *player_constructeur(void)
{
	t_player *to_return;

	if (!(to_return = (t_player*)(malloc(sizeof(t_player)))))
		return (NULL); 
	return (to_return);
}

t_player player_initializer(double pl_x, double pl_y, int deg)
{
	t_player	to_return;

	to_return.pl_x = pl_x;
	to_return.pl_y = pl_y;
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

void left_right(t_player *p, float v, double dir)
{
	if (g_su->key_tab[a_key]/*keycode == 0 || keycode == 113*/) // left
	{
		if (g_su->map[(int)(p->pl_y)][(int)(p->pl_x - sin(dir) * v)] != '1')
			p->pl_x -= sin(dir) * v;
		if (g_su->map[(int)(p->pl_y - cos(dir) * v)][(int)(p->pl_x)] != '1')
			p->pl_y -= cos(dir) * v;
	}
	if (g_su->key_tab[d_key]/*keycode == 2 || keycode == 100*/) // right
	{
		if (g_su->map[(int)(p->pl_y)][(int)(p->pl_x + sin(dir) * v)] != '1')
			p->pl_x += sin(dir) * v; 
		if (g_su->map[(int)(p->pl_y + cos(dir) * v)][(int)(p->pl_x)] != '1')
			p->pl_y += cos(dir) * v;
	}
}

void player_mov(t_player *p/*, int keycode*/)
{	//up 13, down 1, left 0,right 2 (mac)
	float v;
	double dir;
	
	v = .07;//.05; <-- Vitesse de déplacement
	dir = p->player_orient_origin;
	if (g_su->key_tab[w_key]/*keycode == 13 || keycode == 122*/) // up -> devant // seconde condition pour les keycode de linux
	{
		if (g_su->map[(int)(p->pl_y)][(int)(p->pl_x + cos(dir) * v)] != '1')
			p->pl_x += (cos(dir) * v);
		if (g_su->map[(int)(p->pl_y - sin(dir) * v)][(int)(p->pl_x)] != '1')
			p->pl_y -= (sin(dir) * v);
	}
	if (g_su->key_tab[s_key]/*keycode == 1 || keycode == 115*/) // down
	{
		if (g_su->map[(int)(p->pl_y)][(int)(p->pl_x - cos(dir) * v)] != '1')
			p->pl_x -= cos(dir) * v;
		if (g_su->map[(int)(p->pl_y + sin(dir) * v)][(int)(p->pl_x)] != '1')
			p->pl_y += sin(dir) * v;
	}
	left_right(p, v, dir);
}

void player_rotate(t_player *pl/*, int keycode*/)
{
	if ( g_su->key_tab[rightArrow_key]/*keycode == 123 || keycode == 65361*/) // left-arrow // seconde condition pour les keycode de linux
		pl->player_orient_origin += deg_to_rad(2.8);
	else if ( g_su->key_tab[leftArrow_key]/*keycode == 124 || keycode == 65363*/) // right-arrow
		pl->player_orient_origin -= deg_to_rad(2.8);
	//le probleme d'affichage vient de l'orientation... sans savoir encore pourquoi (possible que ce soit pour les 90 et 270°...)
	if (g_su->key_tab[4])
		ft_exit();
}

static inline void clearScreen(void)
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}