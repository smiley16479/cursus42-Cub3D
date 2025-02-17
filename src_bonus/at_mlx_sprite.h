/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_sprite.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:07:26 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/02 12:23:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_SPRITE_H
# define AT_MLX_SPRITE_H
# include "struc.h"
# include "at_mlx_measure.h"

extern	t_app *g_su;
int		which_sprite(char is_a_sprite);
void	init_vector2_d(t_vector2_d *tab, int borne);
void	join_sprites(t_player *p1, t_player *p2);
void	sprite(double *tab, int *t, t_player *pl);

#endif
