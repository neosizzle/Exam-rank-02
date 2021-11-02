#include <stdio.h>

int ft_strchr_custom(char *str, char chr, int idx)
{
	int found;
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == chr)
		{
			found = i;
			break ;
		}
	}
	if (found < idx)
		return (1);
	return (0);
}

int ft_strchr(char *str, char chr)
{
	while (*str)
	{
		if (*str == chr)
			return (1);
		str++;
	}
	return (0);
}

int ft_strlen(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
	}
	return (i);
}

int main(int argc, char **argv)
{
	char 	*str1;
	char 	*str2;
	int 	len1;
	int 	len2;
	int		i;

	if (argc !=3)
	{
		printf("\n");
		return (1);
	}
	str1 = argv[1];
	str2 = argv[2];
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	i = -1;
	if (len1 < len2)
	{
		while (str1[++i])
		{
			char c;

			c = str1[i];
			if (ft_strchr(str2, c) && !ft_strchr_custom(str1, c, i))
			{
				printf("%c", c);
			}
		}
	}
	else
	{
		while (str2[++i])
		{
			char c;

			c = str2[i];
			if (ft_strchr(str1, c) && !ft_strchr_custom(str2, c, i))
			{
				printf("%c", c);
			}
		}
	}
	i = -1;
	printf("\n");
}