/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_app_initializer.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:17:19 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/10 23:50:44 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_APP_INITIALIZER_H
# define AT_APP_INITIALIZER_H

# include <stdlib.h>
# include <mlx.h>
# include "struc.h"
# include "at_image.h"
# include "at_mlx_player_handler.h"

extern	t_app	*g_su;
void    constructor_t_app(void);
void	initializer_t_app(int x, int y, char *title);
void 	application_create_content(void);
void	destructor_t_app(t_app *to_destroy);
void	free_t_app(t_app *to_free);

#endif
