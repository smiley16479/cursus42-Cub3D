/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:58:38 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/01 17:00:17 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "at_mlx_pixel_put.h"

void	p_p(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->size.x || y < 0 || y >= img->size.y)
		return ;
	dst = img->addr + y * img->line_length + x * 4;
	*(unsigned int*)dst = (unsigned int)color;
}
