/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_convert.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:58:34 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/01 15:27:29 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANGLE_CONVERT_H
# define ANGLE_CONVERT_H
# include <math.h>
# include "struc.h"

extern	t_app	*g_su;
void			cst_tab_init(double tab[][361]);
double			deg_to_rad(double degre);
double			rad_to_deg(double rad);
double			atan_sur_360(double angle);

#endif
