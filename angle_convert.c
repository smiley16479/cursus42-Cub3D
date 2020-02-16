/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:58:21 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/14 20:23:34 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "angle_convert.h"



double	deg_to_rad(double degre)
{
	return (degre * M_PI / 180);
}

double	rad_to_deg(double rad)
{
	return (rad / (M_PI / 180));
}

void cst_tab_init(double tab[][361])
{
	int i;

	i = -1;
	while (++i < 360)
		tab[0][i] = cos(deg_to_rad(i));
	i = -1;
	while (++i < 360)
		tab[1][i] = sin(deg_to_rad(i));	
	i = -1;
	while (++i < 360)
		tab[2][i] = tan(deg_to_rad(i));
	// return (tab);
}