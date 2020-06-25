#include <stdio.h>
#include <stdlib.h>

int is_a_charset(char c, char *charset)
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

char **count_strs(char *str, char *charset)
{
	int i;
	int cpt;
	char **strs;

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
	}// le cpt == num sert à verifier le nombre de paramètre sur la ligne
	if ((strs = (char**)malloc(sizeof(*strs) * (cpt + 1))))
	{
		strs[cpt] = NULL;
		// printf("strs : %d\n", cpt);
		return(strs);
	}
	return (NULL);
}

char *ft_alloc_n_copy(int start, int end, char *str)
{
	char *str_cpy;
	int i;

	i = 0;
	if ((str_cpy = (char*)malloc(sizeof(*str_cpy) * (end - start + 1))) == NULL)
		return (NULL);
	while (i < (end - start))
	{
		str_cpy[i] = str[start + i];
		i++;
	}
	str_cpy[i] = 0;
	// printf("strs : %s, str_cpy[1] : %d\n",str_cpy, str_cpy[1]);
	return (str_cpy);
}

char **count_strs_length(char *str, char *charset, char **strs)
{
	int i;
	int cpt;
	int start;
	int end;

	i = 0;
	cpt = 0;
	while(str[i])
	{
		while(is_a_charset(str[i], charset) && str[i])
			i++;
		if(!is_a_charset(str[i], charset) && str[i])
		{	
			start = i;
			while(!is_a_charset(str[i], charset) && str[i])
				i++;
			end = i;
			if ((strs[cpt] = ft_alloc_n_copy(start, end, str)) == NULL)
				return (NULL);
			cpt++;
		}
	}
	//strs[cpt][0] = 0; //dependament de ce que tu veux pour arreter la lecture de **tab -> l60 lui est liée
	return(strs);
}

char **ft_split(char *str, char *charset)
{
	char **tab;
	if ((tab = count_strs(str, charset)) == NULL)
		return (NULL);
	else if ((tab = count_strs_length(str, charset, tab)) == NULL)
		return (NULL);
	return(tab);
}

/* void main()
{
	char *str = "R 1920 1080";
	ft_split(str, " ", 3);
} */