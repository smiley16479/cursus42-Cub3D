/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:07:58 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/06 15:52:22 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_RENDER_H
# define AT_MLX_RENDER_H

# include <math.h>
# include <stdio.h>
# include "angle_convert.h"
# include "at_image.h"
# include "at_mlx_measure.h"
# include "at_mlx_pixel_put.h"
# include "at_mlx_player_handler.h"
# include "at_mlx_shape_square.h"
# include "at_terminal_display.h"
# include "at_bmp.h"
# include "struc.h"

extern	t_app *g_su;

int		render_next_frame(void);
void	display_sprite(int x, int y, t_player *p);
void	display_textured_wall(int x, double distance, t_player *p);

#endif
