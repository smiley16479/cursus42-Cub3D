/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:57:15 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/02 17:59:45 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		is_a_charset(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	**count_strs(char *str, char *charset)
{
	int		i;
	int		cpt;
	char	**strs;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		while (is_a_charset(str[i], charset) && str[i])
			i++;
		if (!is_a_charset(str[i], charset) && str[i])
		{
			while (!is_a_charset(str[i], charset) && str[i])
				i++;
			++cpt;
		}
	}
	if ((strs = (char**)malloc(sizeof(*strs) * (cpt + 1))))
	{
		strs[cpt] = NULL;
		return (strs);
	}
	return (NULL);
}

char	*ft_alloc_n_copy(int start, int end, char *str)
{
	char	*str_cpy;
	int		i;

	i = 0;
	if ((str_cpy = (char*)malloc(sizeof(*str_cpy) * (end - start + 1))) == NULL)
		return (NULL);
	while (i < (end - start))
	{
		str_cpy[i] = str[start + i];
		i++;
	}
	str_cpy[i] = 0;
	return (str_cpy);
}

/*
** 	//strs[cpt][0] = 0; //dependament de ce que tu veux pour
**	arreter la lecture de **tab -> l60 lui est liée
*/

char	**count_strs_length(char *str, char *charset, char **strs)
{
	int i;
	int cpt;
	int start;
	int end;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		while (is_a_charset(str[i], charset) && str[i])
			i++;
		if (!is_a_charset(str[i], charset) && str[i])
		{
			start = i;
			while (!is_a_charset(str[i], charset) && str[i])
				i++;
			end = i;
			if ((strs[cpt] = ft_alloc_n_copy(start, end, str)) == NULL)
				return (NULL);
			cpt++;
		}
	}
	return (strs);
}

char	**ft_split(char *str, char *charset)
{
	char **tab;

	if ((tab = count_strs(str, charset)) == NULL)
		return (NULL);
	else if ((tab = count_strs_length(str, charset, tab)) == NULL)
		return (NULL);
	return (tab);
}
