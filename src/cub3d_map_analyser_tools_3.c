/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_analyser_tools_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:37:04 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/08 12:49:41 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_app_initializer.h"
#include "cub3d_map_analyser.h"

int		is_digit(char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int		ft_atoi(char *str)
{
	long long to_return;

	to_return = 0;
	while (*str)
	{
		to_return *= 10;
		to_return += *str++ - '0';
	}
	if (to_return > __INT32_MAX__)
		to_return = 10000;
	return (to_return);
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
