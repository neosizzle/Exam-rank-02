#include "get_next_line.h"
#include <stdio.h>

int ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
	}
	return (i);
}

char *ft_straddchr(char *str, char chr)
{
	char *result;
	int		i;

	if (!str)
		return "wtf";
	result = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	i = -1;
	while (str[++i])
		result[i] = str[i];
	result[i++] = chr;
	result[i] = 0;
	return result;
}

int get_next_line(char **line)
{
	char	*result;
	char	*temp;
	char	buff[1];
	int		line_found;

	if (!line)
		return (-1);
	line_found = 0;
	result = malloc(1);
	result[0] = 0;
	while (read(0, buff, 1) > 0)
	{
		if(buff[0] == '\n')
		{
			line_found = 1;
			break ;
		}
		temp = ft_straddchr(result, buff[0]);
		free(result);
		result = temp;
	}
	*line = result;
	return line_found;
}

// #include <stdio.h>
// int main()
// {
// 	char 	*str;

// 	printf("%s\n", ft_straddchr(str, 'a'));
// }