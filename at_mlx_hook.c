/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 01:04:06 by adtheus           #+#    #+#             */
/*   Updated: 2020/03/12 14:22:06 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "at_mlx_hook.h"
#include "at_mlx_player_handler.h"
#include "cub3D_map_analyser.h"


int ft_exit()
{
	printf("Je quite\n");
	release_textures();
	// mlx_destroy_image(g_su->mlx, g_su->su_img->img_ptr); //<-- c'est l'image ds le render qui leak

	mlx_destroy_window(g_su->mlx, g_su->mlx_win);
	free(g_su->mlx);
	erase_2dchar(g_su->map);
	exit(0);
}

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

int				at_mlx_hook(t_player *pl)
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
	keycode = convert_key_code_linux(keycode);
	g_su->key_tab[keycode] = 1;
	return (0);
}

int             msg_keyreleased_window(int keycode, t_player *pl)
{
	// printf("keycode released : %d\n", keycode);
	keycode = convert_key_code_linux(keycode);
	g_su->key_tab[keycode] = 0;
	return (0);
}

int             convert_key_code_linux(int keycode)
{
	if (keycode == 65307)//Esc
		return(4);
	if (keycode == 65293)
		return(123);
	if (keycode == 65362)
		return(123);
	if (keycode == 65364)
		return(123);
	if (keycode == 65363) //right array
		return(124);
	if (keycode == 65361) //left array
		return(123);
	if (keycode == 65289) //left array
		return(0);
	if (keycode == 122) //w_key
		return(13);
	if (keycode == 113) //a_key
		return(0);
	if (keycode == 100) //d_key
		return(2);
	if (keycode == 115) //s_key
		return(1);
	if (keycode == 65513)//alt_key
		return(0);
	return(0);	
}