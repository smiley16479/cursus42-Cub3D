/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:09:04 by adtheus           #+#    #+#             */
/*   Updated: 2019/12/23 18:00:00 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "essai.h"
#include "at_mlx_square.h"

int     render_next_frame(void *su)
{
	int color = ((t_data*)(su))->square_shape->color;
	((t_data*)(su))->color_offset += 1;
	// who_wants_a_rainbow((t_data*)(su));
	draw_me_a_square((*(t_data*)su));
    mlx_put_image_to_window(((t_data*)su)->mlx, ((t_data*)su)->mlx_win, ((t_data*)su)->img, 0, 0);
	return (0);
}
