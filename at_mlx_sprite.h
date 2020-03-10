/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_sprite.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:07:26 by adtheus           #+#    #+#             */
/*   Updated: 2020/03/09 15:05:42 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_SPRITE_H
#define AT_MLX_SPRITE_H
#include "struc.h"

extern t_app *g_su;
int		which_sprite(char is_a_sprite);
void    init_vector2_d(t_vector2_d *tab);
void	join_sprites(t_player *p1, t_player *p2);

#endif