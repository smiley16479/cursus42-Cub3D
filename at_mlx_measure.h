#ifndef  AT_MLX_MEASURE_H
# define AT_MLX_MEASURE_H

#ifndef M_PI 
# define M_PI       3.14159265358979323846
#endif
#include "struc.h"

double distance_incorrecte(t_player *pl);
double horizontal_intersection(t_player *pl, double sin, double cos, double tan);
double vertical_intersection(t_player *pl, double cos, double tan);

#endif