
#ifndef AT_MLX_SQUARE_H
# define AT_MLX_SQUARE_H


typedef struct  s_square_struc {
	int		origin_x;
	int		origin_y;
	int		cote;
	int		color;
}               t_square;

t_square	*constructor_t_square(t_square **struc_square);
t_square initializer_t_square(int origin_x,int origin_y, int cote, int color);
// void draw_me_a_square(t_data data); //<- laisser ds le essai.h
int free_t_square(t_square *to_free);
int destructor_t_square(t_square *to_destroy);

#endif