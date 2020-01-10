/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_shape_circle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:17:35 by adtheus           #+#    #+#             */
/*   Updated: 2020/01/10 19:11:11 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include "essai.h"
#include "at_mlx_shape_circle.h"


static inline double deg_to_rad(double degre)
{
	return (degre * M_PI / 180);
}
static inline double rad_to_deg(double rad)
{
	return (rad / (M_PI / 180));
}

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

void draw_me_a_circle(t_data data)
{
	double degre;

	degre = 0;
	while (degre < 180)
	{
		my_mlx_pixel_put(data, ((t_circle*)data.shape)->origin_x + cos(deg_to_rad(degre)) * ((t_circle*)data.shape)->rayon, 
		 	((t_circle*)data.shape)->origin_y + sin(deg_to_rad(degre)) * ((t_circle*)data.shape)->rayon, ((t_circle*)data.shape)->color); //who_wants_a_rainbow(&data));//
		my_mlx_pixel_put(data, ((t_circle*)data.shape)->origin_x - cos(deg_to_rad(degre)) * ((t_circle*)data.shape)->rayon, 
	 		((t_circle*)data.shape)->origin_y - sin(deg_to_rad(degre)) * ((t_circle*)data.shape)->rayon, ((t_circle*)data.shape)->color); //who_wants_a_rainbow(&data));//
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