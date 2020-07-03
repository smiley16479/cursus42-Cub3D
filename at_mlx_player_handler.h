/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_player_handler.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:10 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/02 11:11:12 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_PLAYER_HANDLER_H
# define AT_MLX_PLAYER_HANDLER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "struc.h"
# include "angle_convert.h"

# define W_KEY 	13
# define S_KEY 	1
# define A_KEY 	0
# define D_KEY		2
# define RIGHTARROW 123
# define LEFTARROW 124

int			ft_exit();
void		player_mov_hook(t_player *pl);
void		player_rotate(t_player *pl);
t_player	*player_constructeur(void);
t_player	player_initializer(double pl_x, double pl_y, int deg);

#endif
