/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:17:35 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/15 17:11:04 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include "at_mlx_hook.h"
#include "at_app_initializer.h"
#include "at_mlx_measure.h"
#include "at_mlx_player_handler.h"
#include "at_mlx_render.h"
#include "angle_convert.h"
#include "at_mlx_render.h"
#include "cub3d_map_analyser.h"
#include "at_bmp.h"

/*
**GLOBALE
*/
t_app	*g_su;

int	check_args(int ac, char **av)
{
	int	i;

	g_su->save = 0;
	if (!(ac == 2 || ac == 3))
		print_error(14, g_su->err);
	i = 0;
	while (av[1][i])
		++i;
	if (str_cmp(&(av[1][i - 4]), ".cub"))
		print_error(15, g_su->err);
	if (ac == 3)
		if (str_cmp(av[2], "--save") || !(g_su->save = 1))
			if (str_cmp(av[2], "--old_style") || !(g_su->save = 2))
				print_error(16, g_su->err);
	return (0);
}

int	main(int ac, char **av)
{
	constructor_t_app();
	g_su->err = error_strs_init();
	check_args(ac, av);
	g_su->map = read_map(av[1]);
	if (g_su->save == 0)
		at_mlx_hook(g_su->p);
	mlx_loop_hook(g_su->mlx, render_next_frame, (void*)g_su);
	return (mlx_loop(g_su->mlx));
}
