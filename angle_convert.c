/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:58:21 by adtheus           #+#    #+#             */
/*   Updated: 2020/01/10 16:21:58 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "angle_convert.h"

double deg_to_rad(double degre)
{
	return (degre * M_PI / 180);
}
double rad_to_deg(double rad)
{
	return (rad / (M_PI / 180));
}
