/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_analyser_tools_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:14:02 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/04 17:05:48 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_map_analyser.h"

extern t_app *g_su;

char	**which_ft_split(int info_t, char *str)
{
	char	**arg_strs;
	int		i;
	int		comas;

	if (info_t <= 5)
	{
		if (!(arg_strs = ft_split(str, " ")))
			return (NULL);
	}
	else if (info_t > 5)
	{
		i = -1;
		comas = 0;
		while (str[++i])
			if (str[i] == ',')
				++comas;
		if (comas != 2)
			return (NULL);
		if (!(arg_strs = ft_split(str, " ,")))
			return (NULL);
	}
	else
		return (NULL);
	return (arg_strs);
}

int		check_map_line(char *str, int *player)
{
	if (*str == '\0')
		return (-1);
	while (*str == ' ' || ('0' <= *str && *str <= '2')
		|| *str == 'N' || *str == 'S' || *str == 'E' || *str == 'W')
		if (*str == 'N' || *str == 'S' || *str == 'E' || *str == 'W')
		{
			++*player;
			++str;
		}
		else
			++str;
	if (*str != '\0')
		return (-1);
	return (0);
}

int		which_info_tp(char *str, char *check)
{
	char	*t_orient[8];
	char	**split_return;
	int		i;

	t_orient[0] = "NO";
	t_orient[1] = "SO";
	t_orient[2] = "WE";
	t_orient[3] = "EA";
	t_orient[4] = "S";
	t_orient[5] = "R";
	t_orient[6] = "F";
	t_orient[7] = "C";
	split_return = ft_split(str, " ");
	i = 0;
	while (i < 8 && str_cmp(t_orient[i], *split_return))
		++i;
	if (i < 8 && check[i] == 1)
		print_error(0, g_su->err);
	else if (i < 8)
		check[i] = 1;
	erase_2dchar(split_return);
	return (i);
}

void	duplicate_2dchar_array_part2(char **r, char **strs, int map_len)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		j = -1;
		if ((r[i] = (char*)malloc(map_len)))
		{
			while (strs[i][++j])
				r[i][j] = strs[i][j];
			while (j + 1 < map_len)
				r[i][j++] = ' ';
		}
		else
			print_error(17, g_su->err);
		r[i][j] = 0;
		++i;
	}
}

char	**duplicate_2dchar_array(char **strs, int map_len)
{
	int		i;
	char	**r;

	i = 0;
	while (strs[i])
		++i;
	g_su->ms.y = i;
	g_su->ms.x = map_len - 1;
	if (!(r = (char**)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	r[i] = NULL;
	duplicate_2dchar_array_part2(r, strs, map_len);
	return (r);
}
