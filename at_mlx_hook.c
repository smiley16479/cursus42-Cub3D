#include <mlx.h>
#include <stdio.h>
#include "at_mlx_hook.h"



int             close_window(int keycode, t_vars *vars)
{
	printf("keycode : %d\n", keycode);
	if (keycode == 53) 
    {
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		//and free all your stuff
	}	
	return (0);
}

int             msg_keypressed_window(int keycode, t_vars *vars)
{
	printf("keycode pressed : %d\n", keycode);
	return (0);
}
int             msg_keyreleased_window(int keycode, t_vars *vars)
{
	printf("keycode released : %d\n", keycode);
	return (0);
}