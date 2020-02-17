/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 01:04:06 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/10 21:59:08 by adtheus          ###   ########.fr       */
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

int             msg_keypressed_window(int keycode, t_player *pl)
{
	printf("keycode pressed : %d\n", keycode);
	// printf("keycode pressed\n");
	player_rotate(pl, keycode);
	player_mov(pl, keycode);
	// printf("player_orient_origin : %.3f player_orient : %.3f\n",su->player_orient_origin, su->player_orient);
	return (0);
}
int             msg_keyreleased_window(int keycode, t_player *pl)
{
	printf("keycode released : %d\n", keycode);
	return (0);
}