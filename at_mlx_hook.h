/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_hook.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:47:15 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/01 16:50:31 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_HOOK_H
# define AT_MLX_HOOK_H
# include <mlx.h>
# include "struc.h"

typedef struct	s_vars {
	void		*mlx;
	void		*mlx_win;
}				t_vars;
extern t_app	*g_su;

int				convert_key_code_linux(int keycode);
int				close_window(int keycode);
int				at_mlx_hook(t_player *pl);
int				msg_keypressed_window(int keycode, t_player *pl);
int				msg_keyreleased_window(int keycode, t_player *pl);

#endif
