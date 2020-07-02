/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_color_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:13:26 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/01 16:29:24 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_mlx_color_handler.h"

/*
** return (trgb & 0xFF000000);
*/

int		get_t(int trgb)
{
	return (0xFF & ((char*)(&trgb))[3]);
}

/*
** return (trgb & 0xFF0000);
*/

int		get_r(int trgb)
{
	return (0xFF & ((char*)(&trgb))[2]);
}

/*
** return (trgb & 0xFF00);
*/

int		get_g(int trgb)
{
	return (0xFF & ((char*)(&trgb))[1]);
}

/*
** return (trgb & 0xFF);
*/

int		get_b(int trgb)
{
	return (0xFF & *((char*)(&trgb)));
}

int		get_oposite(int color)
{
	int	opposite_color;

	opposite_color = 0;
	return (opposite_color);
}

void	print_bin(char nb)
{
	unsigned int	i;
	int				ecart;

	// printf("nb : %d\n", (int)nb);
	i = 2147483648;
	ecart = 0;
	while (i > 0)
	{
		nb & i ? write(1, "1", 1) : write(1, "0", 1);
		!(++ecart % 4) && ecart != 32 ? write(1, " ", 1) : 0;
		i /= 2;
	}
	write(1, "\n", 1);
}

int		add_shade(double distance, unsigned int color)
{
	int color_shade;

	color_shade = 255;
	color_shade *= distance;
	color &= 0xFFFFFF00;
	color += color_shade;
	print_bin(color);
	return (color);
}

int		invert_color(int color)
{
	int t;

	t = color & 0x000000FF;
	color = ~color;
	color &= 0xFFFFFF00;
	color += t;
	return (color);
}
