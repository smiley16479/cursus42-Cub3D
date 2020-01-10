/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_shape_square.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:17:35 by adtheus           #+#    #+#             */
/*   Updated: 2020/01/10 19:07:23 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include "essai.h"
#include "at_mlx_shape_square.h"

t_square	*constructor_t_square(t_square **struc_square)
{
	*struc_square = (t_square*)malloc(sizeof(t_square));
	if (*struc_square == NULL)
		return (NULL);
	else
		return (*struc_square);
}

t_square initializer_t_square(int origin_x,int origin_y, int cote, int color)
{
	t_square to_return;
	to_return.origin_x = origin_x;
	to_return.origin_y = origin_y;
	to_return.cote = cote;
	to_return.color = color;
		return (to_return);
}

void draw_me_a_square(t_data data)
{
	int i;
	int j;

	i = 0;
	while (i < data.square_shape->cote)
	{
		j = 0;
		while (j < data.square_shape->cote)
		{
			my_mlx_pixel_put(data, i + data.square_shape->origin_x, 
							j + data.square_shape->origin_y, data.square_shape->color); //who_wants_a_rainbow(&data));//
			++j;
		}
		++i;
	}
}

int free_t_square(t_square **to_free)
{
	free(*to_free);
	return (0);
}

int destructor_t_square(t_square *to_destroy)
{

	return (0);
}