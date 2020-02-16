/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_shape_circle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:17:35 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/11 20:31:09 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_mlx_shape_circle.h"


t_circle	*constructor_t_circle(t_circle **struc_circle)
{
	*struc_circle = (t_circle*)malloc(sizeof(t_circle));
	if (*struc_circle == NULL)
		return (NULL);
	else
		return (*struc_circle);
}

t_circle initializer_t_circle(int origin_x,int origin_y, int rayon, int color)
{
	t_circle to_return;
	to_return.origin_x = origin_x;
	to_return.origin_y = origin_y;
	to_return.rayon = rayon;
	to_return.color = color;
		return (to_return);
}

void draw_me_a_circle(void)
{
	double degre;

	degre = 0;
	while (degre < 180)
	{
		my_mlx_pixel_put(*(g_su->su_img), g_su->su_cicl->origin_x + cos(deg_to_rad(degre)) * g_su->su_cicl->rayon, 
		 	g_su->su_cicl->origin_y + sin(deg_to_rad(degre)) * g_su->su_cicl->rayon, g_su->su_cicl->color); //who_wants_a_rainbow(&data));//
		my_mlx_pixel_put(*(g_su->su_img), g_su->su_cicl->origin_x - cos(deg_to_rad(degre)) * g_su->su_cicl->rayon, 
	 		g_su->su_cicl->origin_y - sin(deg_to_rad(degre)) * g_su->su_cicl->rayon, g_su->su_cicl->color); //who_wants_a_rainbow(&data));//
		++degre;
	}
}

int free_t_circle(t_circle **to_free)
{
	free(*to_free);
	return (0);
}

int destructor_t_circle(t_circle *to_destroy)
{

	return (0);
}