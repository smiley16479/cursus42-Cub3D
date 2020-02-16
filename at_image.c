/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:12:36 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/10 23:39:09 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_image.h"

t_image	create_image(int size_x, int size_y)
{
	t_image ret;

	ret.size = create_vector2(size_x, size_y);
	ret.img_ptr = mlx_new_image(g_su->mlx, ret.size.x, ret.size.y);
	ret.addr = mlx_get_data_addr(ret.img_ptr,
											&(ret.bits_per_pixel),
											&(ret.line_length),
											&(ret.endian));
	return (ret);
}

t_image	*malloc_image(int size_x, int size_y)
{
	t_image *to_return;

	if (!(to_return = (t_image*)malloc(sizeof(t_image))))
		return (NULL);
	*to_return = create_image(size_x, size_y);
	return (to_return);
}

void	destroy_image(t_image *to_destroy)
{
	mlx_destroy_image(g_su->mlx, to_destroy->img_ptr);
	// Ne pas free to_destroy.pixels. Ca fait planter la mlx
}

void free_image(t_image *to_free)
{
	destroy_image(to_free);
	free(to_free);
}