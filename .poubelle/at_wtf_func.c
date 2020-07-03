/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_wtf_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 00:19:49 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/11 00:21:28 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"struc.h"

int who_wants_a_rainbow(t_app *g_su)
{
	// distance /= (708 / 100);
	// printf("ditance : %d et en fl %f, et color avant : %d\n", (int)distance, distance, get_g(*color));
	int *color = &(g_su->square_shape->color);
	int *i = 1;//ANCIENNEMENT->// int *i = &(g_su->color_offset);
	if (*i == 320)
		*i = 0;  
	((char*)color)[u_r] = (char)(sin(0.01 * *i + 0) * 127 + 128);
	((char*)color)[u_g] = (char)(sin(0.01 * *i + 2) * 127 + 128);
	((char*)color)[u_b] = (char)(sin(0.01 * *i + 4) * 127 + 128);

	// printf("color apres ; %d\n", *color);
	return (*color);
}
