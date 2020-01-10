/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_shape_circle.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:58:46 by adtheus           #+#    #+#             */
/*   Updated: 2020/01/10 19:11:31 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AT_MLX_SHAPE_CIRCLE_H
# define AT_MLX_SHAPE_CIRCLE_H


typedef struct  s_circle_struc {
	int		origin_x;
	int		origin_y;
	int		rayon;
	int		color;
}               t_circle;

t_circle	*constructor_t_circle(t_circle **struc_circle);
t_circle initializer_t_circle(int origin_x,int origin_y, int rayon, int color);
// void draw_me_a_circle(t_data data); //<- laisser ds le essai.h
int free_t_circle(t_circle **to_free);
int destructor_t_circle(t_circle *to_destroy);

#endif