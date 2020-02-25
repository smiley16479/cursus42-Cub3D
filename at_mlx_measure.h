/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_measure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 22:40:58 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/25 16:08:29 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_MEASURE_H
# define AT_MLX_MEASURE_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# include <math.h>
# include <mlx.h>
# include <stdio.h>  // est tu oblige de les integrer ?
# include <unistd.h>  // est tu oblige de les integrer ?
# include "struc.h"

extern	t_app *g_su;
enum	e_tab	{e_sin, e_cos, e_tan, e_h, e_v};
double			d_incorrecte(t_player *pl);
double			horizontal_intersection(t_player *pl, double *tab);
double			vertical_intersection(t_player *pl, double *tab);

#endif
