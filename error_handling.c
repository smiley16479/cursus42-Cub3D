/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:49:11 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/02 17:51:56 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_map_analyser.h"

char	**error_strs_init(void)
{
	int		gnl_ret;
	char	**strs;
	char	*str;
	int		fd;

	strs = NULL;
	if ((fd = open("./map/errors.txt", O_RDONLY)) < 0)
		return (NULL);
	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		gnl_ret = gnl(&str, fd);
		strs = gnl_2000(strs, str);
	}
	close (fd);
	return (strs);
}

void    print_error(int nu_of_error, char **strs)
{
	int i;

	i = 0;
	while (strs[nu_of_error][i])
		if (strs[nu_of_error][i] == '\\' && strs[nu_of_error][i + 1] == 'n')
		{
			write(1, "\n", 1);
			i += 2;
		}
		else
			write(1, &(strs[nu_of_error][i++]), 1);
	exit(EXIT_FAILURE);
}

/* void erase_2dchar(char **strs)
**{
**	int i;
**
**	i = 0;
**	if (strs != NULL)
**		while (strs[i])
**			free(strs[i++]);
**	free(strs);
**}
**
**int main()
**{
**	int i;
**	char **strs;
**	i = 0;
**	if ((strs = error_strs_init()))
**		while (strs[i])
**			print_error(i++, strs);
**	erase_2dchar(strs);
**	return (1);
**}
*/
