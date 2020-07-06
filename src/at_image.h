/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_image.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:12:29 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/10 23:15:29 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_IMAGE_H
# define AT_IMAGE_H

# include <stdlib.h>
# include <mlx.h>
# include "struc.h"
# include "at_vector2.h"

extern	t_app	*g_su;
t_image			create_image(int size_x, int size_y);
t_image			*malloc_image(int size_x, int size_y);
void			destroy_image(t_image *to_destroy);
void			free_image(t_image *to_free);

#endif
