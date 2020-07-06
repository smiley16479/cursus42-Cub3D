/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_terminal_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 10:39:52 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/04 11:54:18 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_terminal_display.h"

static inline void	clear_screen(void)
{
	const char	*clear_screen_ansi;

	clear_screen_ansi = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, clear_screen_ansi, 10);
}

/*
** tab[0] = hauteur
** tab[1] = y
** tab[2] = x
*/

void				display_terminal_sub1(char *screen_str, int *t,
											double x_rad_to_add, double x_rad)
{
	t[2] = -1;
	while (++t[2] < g_su->size.x)
	{
		x_rad -= x_rad_to_add;
		g_su->p->player_orient -= x_rad_to_add;
		t[0] = g_su->e_dist / distance(g_su->p, x_rad);
		t[1] = -1;
		while (++t[1] < g_su->size.y)
			if (t[2] == g_su->size.x - 1)
				screen_str[t[2] + (g_su->size.x * t[1])] = '\n';
			else
			{
				if (t[1] >= (g_su->size.y - t[0]) / 2 && t[1] <
													(g_su->size.y + t[0]) / 2)
					screen_str[t[2] + (g_su->size.x * t[1])] = '!' +
																g_su->p->w_o;
				else
					screen_str[t[2] + (g_su->size.x * t[1])] = ' ';
			}
	}
}

void				display_terminal(void)
{
	char	*screen_str;
	int		t[3];
	double	x_rad_to_add;
	double	x_rad;

	x_rad_to_add = deg_to_rad(60. / g_su->size.x);
	x_rad = deg_to_rad(30);
	g_su->p->player_orient = g_su->p->player_orient_origin + x_rad;
	if (!(screen_str = malloc((g_su->size.x * g_su->size.y + 1))))
		return ;
	display_terminal_sub1(screen_str, t, x_rad_to_add, x_rad);
	clear_screen();
	write(1, screen_str, g_su->size.x * g_su->size.y);
	free(screen_str);
}
