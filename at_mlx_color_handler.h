/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_color_handler.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:15:07 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/23 21:39:10 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_COLOR_HANDLER_H
# define AT_MLX_COLOR_HANDLER_H
#include <unistd.h>
#include <stdio.h>

int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		get_oposite(int color);
void	print_bin(char nb);
int		add_shade(double distance, unsigned int color);
int		invert_color(int color);

#endif