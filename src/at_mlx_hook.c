/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 01:04:06 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/15 17:08:31 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "at_mlx_hook.h"
#include "at_mlx_player_handler.h"
#include "cub3d_map_analyser.h"

/*
**int		ft_exit(void)
**{
**	printf("Je quite\n");
**	release_textures();
**	// mlx_destroy_image(g_su->mlx, g_su->su_img->img_ptr);
**  //<-- c'est l'image ds le render qui leak (ligne au dessus)
**	mlx_destroy_window(g_su->mlx, g_su->mlx_win); <- retiré pour le --save
**	free(g_su->mlx);
**	erase_2dchar(g_su->map);
**	exit(0);
**}
*/

int		ft_exit(void)
{
	release_textures();
	free(g_su->mlx);
	erase_2dchar(g_su->map);
	exit(0);
}

/*
**int		close_window(int keycode)
**{
**	printf("keycode : %d\n", keycode);
**	if (keycode == 53)
**		mlx_destroy_window(g_su->mlx, g_su->mlx_win);
**	return (0);
**}
*/

/*
**	Voici les hook pour les interuptions de touches
**	 mlx_key_hook(g_su->mlx_win, close_window, g_su);
**	 mlx_do_key_autorepeaton(g_su->mlx);
*/

int		at_mlx_hook(t_player *pl)
{
	mlx_hook(g_su->mlx_win, 2, 1L << 0, msg_keypressed_window, pl);
	mlx_hook(g_su->mlx_win, 3, 1L << 1, msg_keyreleased_window, pl);
	mlx_hook(g_su->mlx_win, 17, 0, ft_exit, (void*)0);
	return (0);
}

/*
**	Linux Defined in Makefile
*/

int		msg_keypressed_window(int keycode, t_player *pl)
{
	(void)pl;
	if (LINUX)
		keycode = convert_key_code_linux(keycode);
	g_su->key_tab[keycode] = 1;
	return (0);
}

int		msg_keyreleased_window(int keycode, t_player *pl)
{
	(void)pl;
	if (LINUX)
		keycode = convert_key_code_linux(keycode);
	g_su->key_tab[keycode] = 0;
	return (0);
}

int		convert_key_code_linux(int keycode)
{
	if (keycode == 65307)
		return (4);
	if (keycode == 65293)
		return (123);
	if (keycode == 65361 || keycode == 65362 || keycode == 65364)
		return (123);
	if (keycode == 65363)
		return (124);
	if (keycode == 65289)
		return (0);
	if (keycode == 122 || keycode == 119)
		return (13);
	if (keycode == 113)
		return (0);
	if (keycode == 100)
		return (2);
	if (keycode == 115)
		return (1);
	if (keycode == 65513)
		return (0);
	return (0);
}

/*
**	if (keycode == 65307)//Esc
**	if (keycode == 65363) //right array
**		return (124);
**	if (keycode == 65361) //left array
**		return (123);
**	if (keycode == 65289) //left array
**		return (0);
**	if (keycode == 122) //W_KEY
**		return (13);
**	if (keycode == 113) //A_KEY
**		return (0);
**	if (keycode == 100) //D_KEY
**		return (2);
**	if (keycode == 115) //S_KEY
**		return (1);
**	if (keycode == 65513)//alt_key
*/
