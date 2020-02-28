/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 01:04:06 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/27 14:45:10 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "at_mlx_hook.h"
#include "at_mlx_player_handler.h"



int             close_window(int keycode)
{
	printf("keycode : %d\n", keycode);
	if (keycode == 53) 
    {
		mlx_destroy_window(g_su->mlx, g_su->mlx_win);
		//and free all your stuff
	}	
	return (0);
}

int				at_mlx_hook_loop(t_player *pl)
{
	//Voici les hook pour les interuptions de touches
	// mlx_key_hook(g_su->mlx_win, close_window, g_su);
	// mlx_do_key_autorepeaton(g_su->mlx);
	mlx_hook(g_su->mlx_win, 2, 1L<<0, msg_keypressed_window, pl);
	mlx_hook(g_su->mlx_win, 3, 1L<<1, msg_keyreleased_window, pl);

	return(0);
}


int             msg_keypressed_window(int keycode, t_player *pl)
{
	// printf("keycode pressed : %d\n", keycode);
	// printf("keycode pressed\n");
	g_su->key_tab[keycode] = 1;
	// player_rotate(pl, keycode);
	// player_mov(pl, keycode);
	// printf("player_orient_origin : %.3f player_orient : %.3f\n",su->player_orient_origin, su->player_orient);
	return (0);
}

int             msg_keyreleased_window(int keycode, t_player *pl)
{
	g_su->key_tab[keycode] = 0;
	// printf("keycode released : %d\n", keycode);
	return (0);
}