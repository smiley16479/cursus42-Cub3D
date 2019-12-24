#ifndef AT_MLX_HOOK_H
# define AT_MLX_HOOK_H
#include <mlx.h>

typedef struct  s_vars {
    void        *mlx;
    void        *mlx_win;
}               t_vars;

int             close_window(int keycode, t_vars *vars);
int             msg_keypressed_window(int keycode, t_vars *vars);
int             msg_keyreleased_window(int keycode, t_vars *vars);

#endif