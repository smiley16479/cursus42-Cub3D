/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:17:35 by adtheus           #+#    #+#             */
/*   Updated: 2020/01/10 19:10:08 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AT_MLX_ESSAI
#define AT_MLX_ESSAI

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include "at_mlx_shape_square.h"

enum color {u_b, u_g, u_r, u_a};

/* // --> mis ds le square.h
typedef struct  s_square_struc {
	int		origin_x;
	int		origin_y;
	int		cote;
	int		color;
}               t_square;
*/

typedef struct  s_line_struc {
	int		origin_x;
	int		origin_y;
	int		fin_x;
	int		fin_y;
	int		color;
}               t_line;

typedef  struct s_data {
	void		*mlx;
    void    	*mlx_win;
    void        *img;
	void		*su;
    char        *addr;
	char 		*str_error;
	// int 		*map;
	char		*map[5];
	int			window_width;
	int			window_heigth;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			color_offset;
	double		player_x;
	double		player_y;
	double		player_orient;

	t_square	*square_shape;
	t_line		*line_shape;
	void		*shape;
	// t_shape		*circle_shape;
	// t_shape		*tiangle_shape;
}               t_data;

/**Square**/
//t_square	*constructor_t_square(t_square **struc_square);
//t_square initializer_t_square(int origin_x,int origin_y, int cote, int color);
void draw_me_a_square(t_data data); 
//int free_t_square(t_square to_free);
//int destructor_t_square(t_square to_destroy);

int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			get_oposite(int color);
void		print_bin(char nb);
int			add_shade(double distance, unsigned int color);
int			invert_color(int color);
void		my_mlx_pixel_put(t_data data, int x, int y, int color);
t_data		*constructor_t_data(t_data **img);
t_line		*constructor_t_line(t_line **struc_line);
t_data		initializer_t_data(int window_width, int window_heigth);
int 		who_wants_a_rainbow(t_data *su);
void		draw_me_a_line(t_data data);
void		draw_me_a_circle(t_data data);

#endif