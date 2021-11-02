#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct format 
{
	int	perc;
	int	width;
	int letter_count;
};

void	clear_format(struct format *format)
{
	format->perc = 0;
	format-> width = 0;
}

int ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
	}
	return i;
}


int ft_atoi(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == 9)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void mark_flags(char *str, int *i, struct format* format)
{
	int offset;

	// offset = 0;
	// while (str[*i + offset] && str[*i + offset] >= '0' && str[*i + offset] <= '9' )
	// 	offset++;
	// format->width = ft_atoi(str + *i);
	// *i = offset;
	// if (str[*i] == '.')
	// {
	// 	offset = *i;

	// }
	// printf("Width : %d, Perc : %d\n", format->width, format->perc);
}

int ft_printf(char *str, ... )
{
	int	i;
	va_list	valist;
	struct format *format;

	if (!str)
		return 0;
	va_start(valist, str);
	i = -1;
	format = (struct format *)malloc(sizeof(format));
	format->letter_count = 0;
	while (++i < ft_strlen(str))
	{
		clear_format(format);
		if (str[i] != '%')
		{
			ft_putchar(str[i]);
			format->letter_count++;
		}
		else
		{
			++i;
			mark_flags(str, &i, format);
		}
		
	}
	
}

int main(int argc, char const *argv[])
{
	// int ret = ft_printf("123456789\n");
	// printf("%d\n", ret);
	ft_printf(argv[1]);
	return 0;
}
