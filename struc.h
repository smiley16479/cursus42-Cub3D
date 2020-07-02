/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:03:27 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/02 18:25:39 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_MLX_STRUC_H
# define AT_MLX_STRUC_H
# define MS 11

enum	e_orient {SUD_rouge, NORD_vert, EST_bleu, OUEST_jaune};
enum	e_color {u_b, u_g, u_r, u_a};

typedef	struct	s_vector2 {
	int		x;
	int		y;
}				t_vector2;

/*
** s_d = s_distance
*/

typedef	struct	s_vector2_d {
	double		s_d;
	double		s_imp;
	int			sprite;
}				t_vector2_d;

typedef struct	s_line_struc {
	int		origin_x;
	int		origin_y;
	int		fin_x;
	int		fin_y;
	int		color;
}				t_line;

typedef struct	s_square_struc {
	int		origin_x;
	int		origin_y;
	int		cote;
	int		color;
}				t_square;

typedef struct	s_circle_struc {
	int		origin_x;
	int		origin_y;
	int		rayon;
	int		color;
}				t_circle;

/*
** Structure de gestion des textures
**	char		*t_t[6]; //text_tab
**	int			text_bits_per_pixel[6];
**	int			text_line_length[6];
**	int			t_w[6]; // text_width
**	int			t_h[6]; //text_height
**	int			endian[6];
**	t_vector2	fc; //floor ceiling color
*/

typedef struct	s_textur {
	void		*text[6];
	char		*t_t[6];
	int			text_bits_per_pixel[6];
	int			text_line_length[6];
	int			t_w[6];
	int			t_h[6];
	int			endian[6];
	t_vector2	fc;
}				t_textur;

/*
**IL etqit question de precqlculer les cos,sin,tan (cst) ds s_player
**	// double		cst_tab[3][361];
*/

typedef struct	s_player {
	double		pl_x;
	double		pl_y;
	double		player_orient;
	double		player_orient_origin;
	double		dist;
	double		wall_impact;
	int			w_o;
	int			s_num;
	t_vector2_d	s_v2[100];
}				t_player;

typedef struct	s_image {
	t_vector2	size;
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct	s_app {
	void		*mlx;
	void		*mlx_win;
	t_vector2	size;
	int			e_dist;
	char		**map;
	t_vector2	ms;
	char		sprite_tab[10];
	int			key_tab[300];
	char		**err;
	int			save;

	t_player	*p;
	t_image		*su_img;
	t_textur	*t;
	t_square	*square_shape;
	t_line		*line_shape;
	t_circle	*su_cicl;
	void		*shape;
}				t_app;

#endif
