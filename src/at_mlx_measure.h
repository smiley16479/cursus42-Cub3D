/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_measure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 22:40:58 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/01 16:58:22 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_MEASURE_H
# define AT_MLX_MEASURE_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# include <math.h>
# include <mlx.h>
# include "struc.h"
# include "at_mlx_sprite.h"
# include "angle_convert.h"

extern	t_app *g_su;
enum	e_tab	{e_sin, e_cos, e_tan, e_h, e_v, e_x_rad};
double			distance(t_player *pl, double x_rad);
double			horizontal_intersection(t_player *pl, double *tab);
double			vertical_intersection(t_player *pl, double *tab);

#endif
