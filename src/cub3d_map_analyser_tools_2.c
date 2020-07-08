/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_analyser_tools_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:25:12 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/08 12:24:20 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_map_analyser.h"

extern t_app *g_su;

void	check_info_num(char *check)
{
	int i;

	i = 0;
	while (i < 8)
		if (check[i++] == 0)
			print_error(1, g_su->err);
}

int		str_cmp(char *str1, char *str2)
{
	int i;

	if (str2 == NULL)
		print_error(9, g_su->err);
	i = 0;
	while (str1[i] == str2[i] && str2[i] && str1[i])
		++i;
	return (str1[i] - str2[i]);
}

int		len(char *str)
{
	char *tmp;

	tmp = str;
	while (*str++)
		;
	return (str - tmp);
}

void	erase_2dchar(char **strs)
{
	int i;

	i = 0;
	if (strs != NULL)
		while (strs[i])
			free(strs[i++]);
	free(strs);
}

int		check_no_empty_line_in_2dchar(char **strs)
{
	int i;

	i = -1;
	while (strs[++i])
		if (*(strs[i]) == '\0' && strs[i + 1] != NULL)
			if (*(strs[i + 1]) != '\0')
				return (-1);
	return (0);
}
