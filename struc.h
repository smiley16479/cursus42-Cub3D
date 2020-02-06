/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:03:27 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/06 18:54:11 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AT_MLX_STRUC
#define AT_MLX_STRUC

#define MAP_SIDE 10

enum orient {SUD_rouge, NORD_vert, EST_bleu, OUEST_jaune};

typedef struct  s_line_struc {
	int		origin_x;
	int		origin_y;
	int		fin_x;
	int		fin_y;
	int		color;
}               t_line;


typedef struct  s_square_struc {
	int		origin_x;
	int		origin_y;
	int		cote;
	int		color;
}               t_square;

// Structure de gestion des textures
typedef  struct s_textu_data {
	void        *text;
    char        *addr;
	int         text_bits_per_pixel;
    int         text_line_length;
    int     	text_width;
    int     	text_height;
    int     	endian;
	char		*text_tab[6];
}               t_textu_data;


typedef  struct s_data {
	void		*mlx;
    void    	*mlx_win;
    void        *img;
	void		*su;
    char        *addr;
	char 		*str_error;
	char		*map[MAP_SIDE];
	int			window_width;
	int			window_heigth;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			color_offset;
	double		player_x;
	double		player_y;
	double		player_orient;
	double		player_orient_origin;
	int			wall_orient;

	t_square	*square_shape;
	t_line		*line_shape;
	void		*shape;
	void		*text;
}               t_data;

# endif