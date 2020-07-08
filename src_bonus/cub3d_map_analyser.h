/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_analyser.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 12:53:13 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/04 12:50:23 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MAP_ANALYSER_H
# define CUB3D_MAP_ANALYSER_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include "struc.h"

# ifndef M_PI
#  define M_PI    3.14159265358979323846
# endif

/*
**map_info_init.c
*/

void	release_textures(void);
void	release_window(void);
void	parse_info(int info_t, char **info);
int		gnl(char **line, int fd);
char	**gnl_2000(char **strs, char *str);
char	**ft_split(char *str, char *charset);

/*
** cub3D_map_analyser.c
*/

char	**read_map(char *map_path);
void	player_location_2darray(char **map, t_player *lst);
int		check_map(char ***map_txt, char *check, int file, int *str_len);
char	**error_strs_init(void);

/*
** cub3D_map_analyser_tools1.c
*/
char	**which_ft_split(int info_t, char *str);
int		which_info_tp(char *str, char *check);
int		check_map_line(char *str, int *player);
char	**duplicate_2dchar_array(char **strs, int map_len);

/*
** cub3D_map_analyser_tools2.c
*/
void	check_info_num(char *check);
int		str_cmp(char *str1, char *str2);
int		len(char *str);
void	erase_2dchar(char **strs);
int		check_no_empty_line_in_2dchar(char **strs);

/*
** cub3D_map_analyser_tools3.c
*/
void	print_error(int nu_of_error, char **strs);
int		c_b_2d_array(char **map, int x, int y);
void	display_map_2d_ptr(char **map);
int		is_digit(char *str);
int		ft_atoi(char *str);

#endif
