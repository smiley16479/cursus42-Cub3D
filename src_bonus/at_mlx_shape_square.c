/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_shape_square.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:17:35 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/06 16:15:37 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_mlx_shape_square.h"

t_square	*constructor_t_square(t_square **struc_square)
{
	*struc_square = (t_square*)malloc(sizeof(t_square));
	if (*struc_square == NULL)
		return (NULL);
	else
		return (*struc_square);
}

t_square	initializer_t_square(int origin_x, int origin_y,
int cote, int color)
{
	t_square to_return;

	to_return.origin_x = origin_x;
	to_return.origin_y = origin_y;
	to_return.cote = cote;
	to_return.color = color;
	return (to_return);
}

void		draw_me_a_square(void)
{
	int i;
	int j;

	i = 0;
	while (i < g_su->square_shape->cote)
	{
		j = 0;
		while (j < g_su->square_shape->cote)
		{
			p_p(g_su->su_img, i + g_su->square_shape->origin_x,
							j + g_su->square_shape->origin_y,
						g_su->square_shape->color);
			++j;
		}
		++i;
	}
}

void		draw_me_a_life_bar(void)
{
	int i;
	int j;

	i = 0;
	while (i < g_su->size.x * 2 / 5)
	{
		j = 0;
		while (j < g_su->size.y / 50)
		{
			p_p(g_su->su_img, i + g_su->size.x / 50,
							j + g_su->size.y / 50, 0x00FF0000);
			++j;
		}
		++i;
	}
}

/*
** int free_t_square(t_square **to_free)
**{
**	free(*to_free);
**	return (0);
**}
**
**int destructor_t_square(t_square *to_destroy)
**{
**	(void)to_destroy;
**	return (0);
**}
*/
