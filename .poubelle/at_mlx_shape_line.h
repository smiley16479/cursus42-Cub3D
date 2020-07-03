/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_shape_line.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:38:27 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/10 21:38:46 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_SHAPE_LINE_H
# define AT_MLX_SHAPE_LINE_H

#include "struc.h"

t_line	*constructor_t_line(t_line **struc_line);
t_line 	initializer_t_line(int origin_x,int origin_y, int fin_x,int fin_y,int color);
void 	draw_me_a_line(t_app data);

#endif