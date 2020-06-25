#include "cub3D_map_analyser.h"

extern t_app *g_su;

void check_info_num(char *check)
{
	int i;

	i = 0;
	while (i < 8)
		if (check[i++] == 0)
			print_error(1, g_su->err);
}


int str_cmp(char *str1, char *str2)
{
	int i;

	if (str2 == NULL)
		print_error(9, g_su->err);
	i = 0;
	while (str1[i] == str2[i] && str2[i] && str1[i])
		++i;
	return (str1[i] - str2[i]);
}

int len(char *str)
{
    char *tmp = str;
    while (*str++);
    return (str - tmp);
}


void erase_2dchar(char **strs)
{
	int i;

	i = 0;
	if (strs != NULL)
		while (strs[i])
			free(strs[i++]);
	free(strs);
}

/* void main()
{
char **str = NULL;
	erase_2dchar(str);
} */