#include "cub3d_map_analyser.h"
#define BUFF_SIZE 10

int		alloc_line_sub1(int *t, char **tmp, char *buf, char **line)
{
	if (*line != NULL)
		while ((*line)[t[0]])
			++t[0];
	while (buf[t[1]] && buf[t[1]] != '\n')
		++t[1];
	if (!((*tmp) = (char*)malloc(sizeof(char) * (t[0] + t[1] + 1))))
		return (-1);
	t[0] = 0;
	if (*line != NULL)
		while ((*line)[t[0]])
		{
			(*tmp)[t[0]] = (*line)[t[0]];
			++t[0];
		}
	t[1] = 0;
	while (buf[t[1]] && buf[t[1]] != '\n')
	{
		(*tmp)[t[0] + t[1]] = buf[t[1]];
		++t[1];
	}
	(*tmp)[t[0] + t[1]] = '\0';
	return (0);
}


int		alloc_line(char **line, char *buf)
{
	int t[3];
	char *tmp;
	
	t[0] = 0;
	t[1] = 0;
	t[2] = 0;
	if (alloc_line_sub1(t, &tmp, buf, line))
		return (-1);
	t[0] = 0;
	if (buf[t[1]] == '\n' && ++t[1] && (t[2] = 1))
	{
		while (buf[t[1]])
			buf[t[0]++] = buf[t[1]++];
		buf[t[0]] = '\0';
	}
	free(*line);
	*line = tmp;
	return (t[2]);
}

int		gnl(char **line, int fd)
{
	int			ret;
	int			read_ret;
	static char	buf[BUFF_SIZE + 1];

	ret = 0;
	read_ret = 1;
	if (line == NULL)
		return (-1);
	*line = NULL;
	while ((ret = alloc_line(line, buf)) == 0 && read_ret != 0)
	{
		read_ret = read(fd, buf, BUFF_SIZE);
		buf[read_ret] = '\0';
	}
	return (ret > 0 && read_ret ? 1 : 0);
}

/*
**int main()
**{
**	int ret;
**	char *line;
**	int fd =   open("map.txt", O_RDONLY);
**	while ((ret = gnl(&line, fd)) == 1)
**	{
**		printf("ret : %d, *line : %s\n", ret, line);
**		free(line);
**	}
**	printf("ret : %d, *line : %s\n", ret, line);
**	free(line);
**}
*/
