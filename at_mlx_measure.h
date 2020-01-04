#ifndef  AT_MLX_MEASURE_H
# define AT_MLX_MEASURE_H

#ifndef M_PI 
# define M_PI       3.14159265358979323846
#endif
int player_init_pos(t_data *su);
void player_mov(t_data *su, int keycode);
int measure(t_data *su);

#endif