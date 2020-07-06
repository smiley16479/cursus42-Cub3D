/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_player_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:21:25 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/06 12:02:00 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_mlx_player_handler.h"

#ifndef M_PI
# define M_PI       3.14159265358979323846
#endif

t_player	*player_constructeur(void)
{
	t_player *to_return;

	if (!(to_return = (t_player*)(malloc(sizeof(t_player)))))
		return (NULL);
	return (to_return);
}

/*
**	t_player	to_return;
**
**	to_return.pl_x = pl_x;
**	to_return.pl_y = pl_y;
**	to_return.player_orient = 0;
**	to_return.player_orient_origin = deg_to_rad(deg);
**	// cst_tab_init(to_return.cst_tab);
**	// if (!(to_return.key_tab = (int*)malloc(sizeof(int) * 250)))
**		// return (to_return);
**	// i = -1;
**	// while (++i < 10)
**		// (to_return.key_tab)[i] = 0;
**	return (to_return);
*/

t_player	player_initializer(double pl_x, double pl_y, int deg)
{
	t_player	to_return;

	to_return.pl_x = pl_x;
	to_return.pl_y = pl_y;
	to_return.player_orient = 0;
	to_return.player_orient_origin = deg_to_rad(deg);
	return (to_return);
}

void		player_rotate(t_player *pl)
{
	if (g_su->key_tab[RIGHTARROW])
		pl->player_orient_origin += deg_to_rad(2.8);
	else if (g_su->key_tab[LEFTARROW])
		pl->player_orient_origin -= deg_to_rad(2.8);
	if (g_su->key_tab[4] || g_su->key_tab[ESC])
		ft_exit();
}

void		left_right(t_player *p, float v, double dir)
{
	if (g_su->key_tab[A_KEY])
	{
		if (p->pl_x - sin(dir) * v < g_su->ms.x && p->pl_x - sin(dir) * v > 0)
			p->pl_x -= sin(dir) * v;
		if (p->pl_y - cos(dir) * v < g_su->ms.y && p->pl_y - cos(dir) * v > 0)
			p->pl_y -= cos(dir) * v;
	}
	if (g_su->key_tab[D_KEY])
	{
		if (p->pl_x + sin(dir) * v < g_su->ms.x && p->pl_x + sin(dir) * v > 0)
			p->pl_x += sin(dir) * v;
		if (p->pl_y + cos(dir) * v < g_su->ms.y && p->pl_y + cos(dir) * v > 0)
			p->pl_y += cos(dir) * v;
	}
	player_rotate(p);
}

/*
**	if (g_su->key_tab[W_KEY]) // keycode == 13 || keycode == 122
**	up -> devant // seconde condition pour les keycode de linux
**
** v = .07;//.05; <-- Vitesse de déplacement
**
**	//up 13, down 1, left 0,right 2 (mac)
*/

void		player_mov_hook(t_player *p)
{
	float	v;
	double	dir;

	v = .07;
	dir = p->player_orient_origin;
	if (g_su->key_tab[W_KEY])
	{
		if (p->pl_x + cos(dir) * v < g_su->ms.x && p->pl_x + cos(dir) * v > 0)
			p->pl_x += (cos(dir) * v);
		if (p->pl_y - sin(dir) * v < g_su->ms.y && p->pl_y - sin(dir) * v > 0)
			p->pl_y -= (sin(dir) * v);
	}
	if (g_su->key_tab[S_KEY])
	{
		if (p->pl_x - cos(dir) * v < g_su->ms.x && p->pl_x - cos(dir) * v > 0)
			p->pl_x -= cos(dir) * v;
		if (p->pl_y + sin(dir) * v < g_su->ms.y && p->pl_y + sin(dir) * v > 0)
			p->pl_y += sin(dir) * v;
	}
	left_right(p, v, dir);
}

/*
**	le probleme d'affichage vient de l'orientation... sans savoir encore
**	pourquoi (possible que ce soit pour les 90 et 270°...)
*/
