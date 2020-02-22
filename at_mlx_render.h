/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:07:58 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/19 23:17:56 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AT_MLX_RENDER_H
#define AT_MLX_RENDER_H

#include <math.h>
#include <stdio.h>
#include "at_mlx_measure.h"
#include "at_image.h"
#include "at_mlx_shape_circle.h"
#include "at_mlx_shape_square.h"
#include "angle_convert.h"
#include "struc.h"

extern	t_app *g_su;

int     render_next_frame(t_app *YourStruct);
int     render_next_frame1(void);
void 	display_wall(int x, double distance);
void 	display_textured_wall(int x, double distance, t_player *p);

#endif