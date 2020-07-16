/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_app_initializer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:17:07 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/15 16:55:47 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_app_initializer.h"

void	constructor_t_app(void)
{
	int i;

	g_su = (t_app*)malloc(sizeof(t_app));
	g_su->t = (t_textur*)malloc(sizeof(t_textur));
	g_su->p = player_constructeur();
	i = -1;
	while (++i < 3)
		g_su->sprite_tab[i] = '2' + i;
	g_su->sprite_tab[3] = '\0';
	if (g_su == NULL || g_su->t == NULL || g_su->p == NULL)
		exit(EXIT_FAILURE);
	else
		g_su->mlx = mlx_init();
}

void	initializer_t_app(int x, int y, char *nam)
{
	int i;

	g_su->size = create_vector2(x, y);
	g_su->e_dist = x / 2 / 0.57735;
	g_su->mlx_win = mlx_new_window(g_su->mlx, g_su->size.x, g_su->size.y, nam);
	i = 0;
	while (i < 300)
		g_su->key_tab[i++] = 0;
	g_su->su_img = NULL;
}

void	application_create_content(void)
{
	g_su->su_img = malloc_image(g_su->size.x, g_su->size.y);
}

void	destructor_t_app(t_app *to_destroy)
{
	mlx_destroy_image(to_destroy->mlx, to_destroy->su_img);
	mlx_destroy_window(to_destroy->mlx, to_destroy->mlx_win);
}

void	free_t_app(t_app *to_free)
{
	destructor_t_app(to_free);
	free(to_free);
}
