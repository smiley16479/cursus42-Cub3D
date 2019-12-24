#include <math.h>
#include "essai.h"
#include "at_mlx_measure.h"

int player_init_pos(t_data *su)
{
	char *str = "NSEW";
	int y = -1, x, i;
	while((x = -1) && ++y < 20)
		while((i = -1) && ++x < 20)
			while (str[++i])
				if (su->map[y * 20 + x] == str[i])
				{
					printf("player found on x : %d, y : %d oriented on :%c\n", x + 1, y + 1, str[i]);
					su->player_x = x + 0.5;
					su->player_y = y + 0.5;
					if (i == 0) // il va surement falloir redefinir ça en gradian
						su->player_orient = M_PI / 2; // en gradian 100
					else if (i == 1)
						su->player_orient = 3 * M_PI / 2; //300
					else if (i == 2)
						su->player_orient = M_PI; // 200
					else if (i == 3)
						su->player_orient = 2* M_PI; // 0 ou 400... "gon" <- unite
					return (y * 20 + x);
				}
	return (-1);
}

int player_mov(t_data *su, int keycode)
{
	if (keycode == 13) // up
		su->player_y -= 0.02;
	else if (keycode == 0) // left
		su->player_x -= 0.02;
	else if (keycode == 1) // down
		su->player_y += 0.02;
	else if (keycode == 2) // right
		su->player_x += 0.02;
	return (0);
}

int measure(t_data *su)
{
	if (su->player_orient < 100)
		
	return (0);
}