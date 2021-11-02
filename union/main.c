#include <stdio.h>

int		ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != 0)
	{
	}
	return (i);
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

int	ft_strchr_custom(char *str, char chr, int idx)
{
	int found;
	int i;

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

int main(int argc, char **argv)
{
    char    *str1;
    char    *str2;
    int     i;
	int		len1;
	int		len2;

    if (argc != 3)
    {
        printf("\n");
        return (1);
    }
    i = -1;
	str1 = argv[1];
	str2 = argv[2];
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
    while (++i < len1)
    {
		char	c;

		c = str1[i];
		if (ft_strchr_custom(str1, c, i))
			continue;
		printf("%c", c);
    }
	i = -1;
	while (++i < len2)
    {
		char	c;

		c = str2[i];
		if (ft_strchr_custom(str2, c, i) || ft_strchr(str1, c))
			continue ;
		printf("%c", c);
    }
	printf("\n");
}