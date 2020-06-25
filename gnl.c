#include "cub3D_map_analyser.h"
#define BUFF_SIZE 10


int alloc_line(char **line, char *buf)
{
	int i = 0, j = 0, ret = 0;
	char *tmp;
	if (*line != NULL)
		while ((*line)[i])
			++i;
	while (buf[j] && buf[j] != '\n')
		++j;
	if (!(tmp = (char*)malloc(sizeof(char) * (i + j + 1))))
		return (-1);
	i = 0;
	if (*line != NULL)
		while ((*line)[i])
		{
			tmp[i] = (*line)[i];
			++i;
		}
	j = 0;
	while (buf[j] && buf[j] != '\n')
	{
		tmp[i + j] = buf[j];
		++j;
	}
	tmp[i + j] = '\0';
	i = 0;
	if (buf[j] == '\n' && ++j && (ret = 1))
	{
		while (buf[j])
			buf[i++] = buf[j++];
		buf[i] = '\0';
	}
	free(*line);
	*line = tmp;
	return (ret);
}

int gnl(char **line, int fd)
{
	int ret = 0;
	int read_ret = 1;
	static char buf[BUFF_SIZE + 1];
	if (line == NULL)// || *line == NULL)
		return (-1);
	*line = NULL;
	while ((ret = alloc_line(line, buf)) == 0 && read_ret != 0)
	{
		read_ret = read(fd, buf, BUFF_SIZE);
		buf[read_ret] = '\0';
	}
//	printf("%s\n", *line);
	return (ret > 0 && read_ret ? 1 : 0);
	// return (**line != '\0'  ? 1 : 0);
}


/* int main()
{
	int ret;
	char *line;
	int fd =   open("map.txt", O_RDONLY);
	while ((ret = gnl(&line, fd)) == 1)
	{
		printf("ret : %d, *line : %s\n", ret, line);
		free(line);
	}
	printf("ret : %d, *line : %s\n", ret, line);
	free(line);
}
 */
