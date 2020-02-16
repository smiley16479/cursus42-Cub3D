#ifndef AT_MLX_HOOK_H
# define AT_MLX_HOOK_H
#include <mlx.h>
#include "struc.h"

typedef struct  s_vars {
    void        *mlx;
    void        *mlx_win;
}               t_vars;
extern  t_app   *g_su;
int             close_window(int keycode);
int             msg_keypressed_window(int keycode, t_player *pl); // fonctionne avec une definiton inegale dans l'appel de fonction mlx_loop_hook
int             msg_keyreleased_window(int keycode, t_player *pl);

#endif