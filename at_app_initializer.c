/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_app_initializer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:17:07 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/25 16:18:51 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_app_initializer.h"

t_app	*constructor_t_app(void)
{
	g_su = (t_app*)malloc(sizeof(t_app));
	if (g_su == NULL)
		return (NULL);
	else
		return (g_su);
}

t_app	initializer_t_app(int x, int y, char *title)
{
	t_app to_ret;

	to_ret.mlx = mlx_init();
	to_ret.size = create_vector2(x, y);
	to_ret.mlx_win = mlx_new_window(to_ret.mlx, to_ret.size.x, to_ret.size.y, title);
	 //ceci ne devrait pas marcher // -> 
	// to_ret.su_img = malloc_image(x, y);
	int i = 0;
	while (i < 300)
		to_ret.key_tab[i++] = 0;
	to_ret.su_img = NULL;
	return (to_ret);
}

void application_create_content(void)
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