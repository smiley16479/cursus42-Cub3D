/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_shape_square.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:20:40 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/06 16:29:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_SHAPE_SQUARE_H
# define AT_MLX_SHAPE_SQUARE_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include "struc.h"
# include "at_mlx_pixel_put.h"

extern t_app	*g_su;
t_square		*constructor_t_square(t_square **struc_square);
t_square		initializer_t_square(int origin_x, int origin_y,
		int cote, int color);
void			draw_me_a_square(void);
int				free_t_square(t_square **to_free);
int				destructor_t_square(t_square *to_destroy);
void			draw_me_a_life_bar(void);

#endif
