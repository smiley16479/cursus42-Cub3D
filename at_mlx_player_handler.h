/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_player_handler.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:10 by adtheus           #+#    #+#             */
/*   Updated: 2020/01/16 18:49:38 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_PLAYER_HANDLER
# define AT_MLX_PLAYER_HANDLER
#include "struc.h"

int player_init_pos(t_data *su);
void player_mov(t_data *su, int keycode);
void player_rotate(t_data *su, int keycode);
// static inline void clearScreen(void); // <- Attention ?
void wall_collision_checker(t_data *su, float x, float y);
int getchar_player_mov(t_data *su);
char get_player_pos(t_data *su);
void display_player_orient(t_data *su);
void display_map(char *map[MAP_SIDE], t_data *su);

#endif