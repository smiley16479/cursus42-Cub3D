/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_player_handler.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:10 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/14 19:51:59 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_PLAYER_HANDLER
# define AT_MLX_PLAYER_HANDLER

# include <stdio.h>
# include <stdlib.h> 
# include <unistd.h>
# include "struc.h"
# include "angle_convert.h"

int player_init_pos(void);
void player_mov(t_player *pl, int keycode);
void player_rotate(t_player *pl, int keycode);
// static inline void clearScreen(void); // <- Attention ?
void wall_collision_checker(float x, float y);
int getchar_player_mov(void);
char get_player_pos(void);
void display_player_orient(t_player *pl);
void display_map(char *map[MAP_SIDE]);
t_player *player_constructeur(t_player **to_return);
t_player player_initializer(int player_x, int player_y, int deg);

#endif