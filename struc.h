/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:03:27 by adtheus           #+#    #+#             */
/*   Updated: 2020/03/09 18:12:22 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AT_MLX_STRUC
#define AT_MLX_STRUC

#define MAP_SIDE 11

enum orient {SUD_rouge, NORD_vert, EST_bleu, OUEST_jaune};
enum color {u_b, u_g, u_r, u_a};

typedef	struct	s_vector2 {
	int		x;
	int		y;
}				t_vector2;

typedef	struct	s_vector2_d {
	double		s_dist;
	double		s_impact;
	int			sprite;
}				t_vector2_d;

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

typedef struct  s_circle_struc {
	int		origin_x;
	int		origin_y;
	int		rayon;
	int		color;
}               t_circle;

// Structure de gestion des textures
typedef  struct s_textur {
	void        *text[6];
	char		*text_tab[6];
	int         text_bits_per_pixel[6];
    int         text_line_length[6];
    int     	text_width[6];
    int     	text_height[6];
    int     	endian[6];
}               t_textur;

typedef  struct s_player {
	double		player_x;
	double		player_y;
	double		player_orient;
	double		player_orient_origin;
	// double		cst_tab[3][361];
	double		wall_impact;
	int			wall_orient;
	t_vector2_d	sprite_v2[100];
	int			sprite_num;
}				t_player;

typedef  struct s_image {
	t_vector2	size;
    void        *img_ptr;
    char        *addr;
	int         bits_per_pixel;
    int         line_length;
    int         endian;
}				t_image;

typedef  struct s_app {
	void		*mlx;
    void    	*mlx_win;
	t_vector2	size;
	char		*map[MAP_SIDE];
	char		sprite_tab[10];
	int			key_tab[300];

	t_square	*square_shape;
	t_line		*line_shape;
	t_player	*p;
	t_image		*su_img;
	t_textur	*t;
	t_circle	*su_cicl;
	void		*shape;
}               t_app;

# endif