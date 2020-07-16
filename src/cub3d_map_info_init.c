/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_info_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:45:29 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/15 16:55:56 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_app_initializer.h"
#include "cub3d_map_analyser.h"

void				release_textures(void)
{
	int i;

	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(g_su->mlx, g_su->t->text[i++]);
	}
}

void				open_texture(int info_t, char *file_path)
{
	if (!(g_su->t->text[info_t] = mlx_xpm_file_to_image(g_su->mlx,
		file_path,
		&(g_su->t->t_w[info_t]),
		&(g_su->t->t_h[info_t]))))
		print_error(3, g_su->err);
	if (!(g_su->t->t_t[info_t] = mlx_get_data_addr(
		g_su->t->text[info_t],
		&(g_su->t->text_bits_per_pixel[info_t]),
		&(g_su->t->text_line_length[info_t]),
		&(g_su->t->endian[info_t]))))
		print_error(3, g_su->err);
}

/*
** g_su->e_dist = g_su->size.x / 2 / 0.57735;
** // pour une FOV de 60° le 0.5.. correspond à tan(30°)
*/

void				init_resolution(char **info)
{
	int i;

	if (!(is_digit(*info) && is_digit(*(info + 1))))
		print_error(5, g_su->err);
	g_su->size.x = ft_atoi(*info);
	g_su->size.y = ft_atoi(*++info);
	g_su->size.x = g_su->size.x < 2560 ? g_su->size.x : 2560;
	g_su->size.y = g_su->size.y < 1440 ? g_su->size.y : 1440;
	g_su->e_dist = g_su->size.x / 2 / 0.57735;
	if (g_su->save == 0)
		g_su->mlx_win = mlx_new_window(g_su->mlx, g_su->size.x, g_su->size.y,
				"Pinky_WinKi");
	i = 0;
	while (i < 300)
		g_su->key_tab[i++] = 0;
	application_create_content();
}

void				init_fc_color(char **info, char fc)
{
	char	to_affect[4];
	int		color[3];

	if (is_digit(*info) && is_digit(*(info + 1)) && is_digit(*(info + 2)))
		if ((*color = ft_atoi(*info)) <= 255)
			if ((color[1] = ft_atoi(*++info)) <= 255)
				if ((color[2] = ft_atoi(*++info)) <= 255)
				{
					*to_affect = *color;
					to_affect[1] = color[1];
					to_affect[2] = color[2];
					to_affect[3] = 0;
					if (fc == 'f')
						g_su->t->fc.x = *(int*)to_affect;
					else if (fc == 'c')
						g_su->t->fc.y = *(int*)to_affect;
					return ;
				}
	print_error(6, g_su->err);
}

void				parse_info(int info_t, char **info)
{
	int i;

	i = 0;
	while (info[i])
		++i;
	if (info_t <= 4)
	{
		if (i != 1)
			print_error(4, g_su->err);
		open_texture(info_t, *info);
	}
	else if (info_t == 5)
	{
		if (i != 2)
			print_error(5, g_su->err);
		init_resolution(info);
	}
	else if (info_t <= 7)
	{
		if (i != 3)
			print_error(6, g_su->err);
		init_fc_color(info, info_t == 6 ? 'f' : 'c');
	}
}
