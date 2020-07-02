/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_analyser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:13:42 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/02 17:13:47 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_map_analyser.h"
#include <string.h>
#include <errno.h>

/*
**	FYI Meme include que dans at_bmp.c
*/

t_app	*g_su;

char	**check_map_integrity(int file, char ***map_txt, int *str_len)
{
	int		i;
	int		player;
	char	**strs;

	strs = NULL;
	strs = gnl_2000(strs, **map_txt);
	i = 1;
	while (0 < i)
	{
		*str_len = len(**map_txt) > *str_len ? len(**map_txt) : *str_len;
		i = gnl(*map_txt, file);
		strs = gnl_2000(strs, **map_txt);
	}
	i = -1;
	player = 0;
	while (strs[++i])
		if (check_map_line(strs[i], &player))
			print_error(10, g_su->err);
	if (player != 1)
		print_error(11, g_su->err);
	return (strs);
}

int		check_map(char ***map_txt, char *check, int file, int *str_len)
{
	int		info_t;
	char	**arg_strs;

	if ((info_t = which_info_tp(**map_txt, check)) == 8)
	{
		check_info_num(check);
		*map_txt = check_map_integrity(file, map_txt, str_len);
		return (-1);
	}
	if (!(arg_strs = which_ft_split(info_t, **map_txt)))
		print_error(2, g_su->err);
	parse_info(info_t, arg_strs + 1);
	erase_2dchar(arg_strs);
	return (0);
}

int		count_map_line(char *map_path, char ***map_txt)
{
	int		file;
	int		str_len;
	int		gnl_ret;
	char	check[8] = {0};

	str_len = 0;
	gnl_ret = 1;
	if (0 >= (file = open(map_path, O_RDONLY)))
		print_error(18, g_su->err);
	while (0 < gnl_ret)
	{
		if ((gnl_ret = gnl(*map_txt, file)) == -1)
			print_error(7, g_su->err);
		if (***map_txt != '\0')
			if (check_map(map_txt, check, file, &str_len) < 0)
			{
				close(file);
				break ;
			}
		free(**map_txt);
	}
	check_info_num(check);
	close(file);
	return (str_len);
}

/*
** 	char *map_txt1;//= NULL;<-- SI ca plante grande chance que ça vienne de là
*/

char	**read_map(char *map_path)
{
	char		*map_txt1;
	char		**map_txt;
	char		**map_txt_cpy;
	int			map_len;

	map_txt = &map_txt1;
	map_len = count_map_line(map_path, &map_txt);
	player_location_2darray(map_txt, g_su->p);
	map_txt_cpy = duplicate_2dchar_array(map_txt, map_len);
	if (c_b_2d_array(map_txt, g_su->p->pl_x, g_su->p->pl_y))
		print_error(13, g_su->err);
	display_map_2d_ptr(map_txt); // <- le display est ICI
	display_map_2d_ptr(map_txt_cpy); // <- le display est ICI
	erase_2dchar(map_txt);
	// erase_2dchar(map_txt_cpy);// Veut on vrmt supprimer la map ?
	return (map_txt_cpy);
}

void	player_location_2darray(char **map, t_player *p)
{
	int		t[3];
	char	*charset;

	charset = " 012";
	t[1] = -1;
	while (map[++t[1]] && (t[0] = -1))
		while (map[t[1]][++t[0]] && !(t[2] = 0))
			while (map[t[1]][t[0]] != charset[t[2]])
				if (!charset[t[2]++])
				{
					p->pl_x = t[0] + .5;
					p->pl_y = t[1] + .5;
					if (map[t[1]][t[0]] == 'N')
						g_su->p->player_orient_origin = M_PI / 2;
					if (map[t[1]][t[0]] == 'E')
						g_su->p->player_orient_origin = M_PI;
					if (map[t[1]][t[0]] == 'W')
						g_su->p->player_orient_origin = 0;
					if (map[t[1]][t[0]] == 'S')
						g_su->p->player_orient_origin = M_PI * 3 / 2;
					map[t[1]][t[0]] = '0';
					return ;
				}
}

int		c_b_2d_array(char **map, int x, int y)
{
	if (0 > x || 0 > y || !map[y] || !map[y][x])
		return (1);
	if (map[y][x] == ' ')
		print_error(12, g_su->err);
	if (map[y][x] != '0' && map[y][x] != '2')
		return (0);
	map[y][x] = 'k';
	if (c_b_2d_array(map, x + 1, y) || c_b_2d_array(map, x - 1, y) ||
		c_b_2d_array(map, x, y - 1) || c_b_2d_array(map, x, y + 1))
		return (1);
	return (0);
}

void	display_map_2d_ptr(char **map)
{
	int i;

	while (*map && (i = -1))
	{
		while ((*map)[++i])
			write(1, &((*map)[i]), 1);
		++map;
		write(1, "\n", 1);
	}
	write(1, "fin de display_map_2d_ptr\n", 26);
}

/*
**	int main()
**	{
**    t_app su;
**    g_su = &su;
**    t_textur t;
**    g_su->t = &t;
**	t_player p;
**    g_su->p = &p;
**    g_su->err = error_strs_init();
**    // g_su->mlx = mlx_init();
**    read_map("map/map1.txt");
**	// release_textures();
**	// release_window();
**printf("orient : %f, map.sz.x : %d, map.sz.y : %d, player_located : %f,%f\n",
**	g_su->p->player_orient_origin, g_su->ms.x, g_su->ms.y, p.pl_x, p.pl_y);
**    erase_2dchar(g_su->err);
**
**    return (0);
**}
*/
