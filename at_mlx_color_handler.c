/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_color_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:13:26 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/23 21:39:37 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_mlx_color_handler.h"

int		get_t(int trgb)
{
	// return (trgb & 0xFF000000);
	return (0xFF & ((char*)(&trgb))[3]);
}

int		get_r(int trgb)
{
	// return (trgb & 0xFF0000);
	return (0xFF & ((char*)(&trgb))[2]);
}

int		get_g(int trgb)
{
	// return (trgb & 0xFF00);
	return (0xFF & ((char*)(&trgb))[1]);
}

int		get_b(int trgb)
{
	// return (trgb & 0xFF);
	return (0xFF & *((char*)(&trgb)));
}

int get_oposite(int color)
{
	int opposite_color;
	opposite_color = 0;

	return (opposite_color);
}

void print_bin(char nb)
{
	printf("nb : %d\n", (int)nb);
	unsigned int i = 2147483648; // 128; //
	int ecart = 0;
	while (i > 0)
	{
		nb & i ? write(1, "1", 1) : write(1, "0", 1);
	 	!(++ecart % 4) && ecart != 32 ? write(1, " ", 1): 0;
		i /= 2;
	}
	write(1, "\n", 1);
}

int add_shade(double distance, unsigned int color)
{
	int color_shade;

	color_shade = 255;
	color_shade *= distance;
	color &= 0xFFFFFF00;
	color += color_shade;
	print_bin(color);
	return (color);
}

int invert_color(int color)
{
	int t;
	t = color & 0x000000FF;
	color = ~color;
	color &= 0xFFFFFF00;
	color += t;
	return (color);
}