/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 01:04:06 by adtheus           #+#    #+#             */
/*   Updated: 2020/01/13 09:41:32 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "at_mlx_hook.h"
#include "at_mlx_player_handler.h"



int             close_window(int keycode, t_data *vars)
{
	printf("keycode : %d\n", keycode);
	if (keycode == 53) 
    {
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		//and free all your stuff
	}	
	return (0);
}

int             msg_keypressed_window(int keycode, t_data *su)
{
	player_rotate(su, keycode);
	player_mov(su, keycode);
	printf("keycode pressed : %d, player_orient : %.3f\n", keycode, su->player_orient);
	return (0);
}
int             msg_keyreleased_window(int keycode, t_data *su)
{
	printf("keycode released : %d\n", keycode);
	return (0);
}