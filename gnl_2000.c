#include "cub3D_map_analyser.h"
/* 
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
       
int gnl(char **str, int file);

void erase_2dchar(char **strs)
{
	int i;

	i = 0;
	if (strs != NULL)
        while (strs[i])
    		free(strs[i++]);
    free(strs);
}
 */
char **gnl_2000(char **str_strs, char *str)
{
    int i;
    int strs_num;
    char **to_return;

    strs_num = 0;
    if (str_strs != NULL)
        while (str_strs[strs_num])
            ++strs_num;
    if (!(to_return = (char**)malloc(sizeof(char *) * (++strs_num + 1))))
        return (NULL);
    to_return[strs_num] = NULL;
    i = -1;
    while (++i < strs_num)
        if (i == strs_num - 1)
            to_return[i] = str;
        else
            to_return[i] = str_strs[i];
    if (str_strs != NULL)
        free(str_strs);
    return (to_return);
}


/* void main()
{
    int     i = 1;
    char    *str;
    char    **str_strs1 = NULL;//  = (char **)malloc(sizeof(char **));
    *str_strs1 = NULL; // si tu ne le mets pas a null la boucle des strs_num va potentiellement plus loin que prevu 

    int fd;
    fd = open("map.txt", O_RDONLY);
    printf("fd : %d\n", fd);
    while (i > 0)
    {
        i = gnl(&str, fd);
        str_strs1 = gnl_2000(str_strs1, str);
    }
    i = -1;
    while (str_strs1[++i])
        printf("%s\n", str_strs1[i]);
    erase_2dchar(str_strs1);
} */