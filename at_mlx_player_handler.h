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

int player_init_pos(void);
int player_mov_hook(t_player *pl);
void player_mov(t_player *pl/*, int keycode*/);
void player_rotate(t_player *pl/*, int keycode*/);
// static inline void clearScreen(void); // <- Attention ?
void wall_collision_checker(float x, float y);
int getchar_player_mov(void);
char get_player_pos(void);
void display_player_orient(t_player *pl);
void display_map(char *map[MAP_SIDE]);
t_player *player_constructeur(t_player **to_return);
t_player player_initializer(double player_x, double player_y, int deg);

#endif