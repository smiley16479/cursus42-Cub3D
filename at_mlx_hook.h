#ifndef AT_MLX_HOOK_H
# define AT_MLX_HOOK_H
#include <mlx.h>
#include "struc.h"

typedef struct  s_vars {
    void        *mlx;
    void        *mlx_win;
}               t_vars;

int             close_window(int keycode, t_data *vars);
int             msg_keypressed_window(int keycode, t_data *su); // fonctionne avec une definiton inegale dans l'appel de fonction mlx_loop_hook
int             msg_keyreleased_window(int keycode, t_data *su);

#endif