/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_terminal_display.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 10:40:36 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/04 10:52:54 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_TERMINAL_DISPLAY_H
# define AT_TERMINAL_DISPLAY_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "angle_convert.h"
# include "at_mlx_measure.h"
# include "struc.h"

extern t_app *g_su;
static inline void	clear_screen(void);
void				display_terminal(void);

#endif
