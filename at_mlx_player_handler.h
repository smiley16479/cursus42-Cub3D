/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_player_handler.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:10 by adtheus           #+#    #+#             */
/*   Updated: 2020/03/12 16:47:31 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_PLAYER_HANDLER
# define AT_MLX_PLAYER_HANDLER

# include <stdio.h>
# include <stdlib.h> 
# include <unistd.h>
# include "struc.h"
# include "angle_convert.h"

#  define w_key 	13
#  define s_key 	1
#  define a_key 	0
#  define d_key		2
#  define rightArrow_key 123
#  define leftArrow_key 124

int ft_exit();
int player_mov_hook(t_player *pl);
void player_mov(t_player *pl/*, int keycode*/);
void player_rotate(t_player *pl/*, int keycode*/);
// static inline void clearScreen(void); // <- Attention ?
t_player *player_constructeur(void);
t_player player_initializer(double pl_x, double pl_y, int deg);

#endif