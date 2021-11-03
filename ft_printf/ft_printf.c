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

void ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
	
}

int is_conversions(char c)
{
	if (c == 's' || c == 'd' || c == 'x')
		return 1;
	return 0;
}

int is_numdot(char c)
{
	if (c <= '9' && c >= '0')
		return 1;
	if (c == '.')
		return 1;
	return 0;
}

char	*ft_strdup(char *str)
{
	char *res;
	int	i;

	res = malloc(sizeof(char) *( 1 + ft_strlen(str) ));
	i = -1;
	while (++i)
		res[i] = str[i];
	res[i] = 0;
	return res;
}

char	*ft_strtrim(char *str, int length)
{
	int		i;
	char	*res;

	i = -1;
	res = (char *)malloc(sizeof(char) * (length + 1));
	if (!length)
	{
		res[0] = 0;
		return res;
	}
	while (++i < length)
	{
		res[i] = str[i];
		//printf("res i : %c, str i : %c\n", res[i], str[i]);
	}
	res[i] = 0;
	//printf("res : %s\n", res);
	return res;	
}

void	print_spaces(struct format *format)
{
	int	i;

	i = -1;
	while (++i < format->width)
	{
		ft_putchar(' ');
	}
}

void mark_flags(char *str, int *i, struct format* format)
{
	int offset;
	int	init_i;

 	format->width = ft_atoi(str + *i);
	offset = 0;
	init_i = *i;
	while (str[*i + offset] && str[*i + offset] <= '9' && str[*i + offset] >= '0')
	{
		offset++;
	}
	if (str[*i + offset] == '.')
		format->perc = ft_atoi(str + *i + offset + 1);
	while (is_numdot(str[*i]))
		(*i)++;

	// offset = 0;
	// while (str[*i + offset] && str[*i + offset] >= '0' && str[*i + offset] <= '9' )
	// 	offset++;
	// format->width = ft_atoi(str + *i);
	// *i = offset;
	// if (str[*i] == '.')
	// {
	// 	offset = *i;

	// }
	//printf("Width : %d, Perc : %d, init i : %d, i %d\n", format->width, format->perc, init_i, *i);
}

void	process_str(struct format *format, va_list valist)
{
	char	*str_raw;
	char	*str_trimmed;
	int		is_null;

	str_raw = va_arg(valist, char *);

	//check null
	is_null = 0;
	if (!str_raw)
	{
		is_null = 1;
		str_raw = "(null)";
	}

	//adjust percision
	if (format->perc > ft_strlen(str_raw))
		format->perc = ft_strlen(str_raw);
	str_trimmed = ft_strtrim(str_raw, format->perc);
	if (is_null && format->perc < ft_strlen(str_raw))
		str_trimmed = ft_strdup("");

	//adjust width
	format->width = format->width - ft_strlen(str_trimmed);
	if (format->width < 0)
		format->width = 0;
	print_spaces(format);

	//print string
	//printf("str_trimmed : %s, str_raw: %s\n", str_trimmed, str_raw);
	ft_putstr(str_trimmed);
	format->letter_count += format->width + ft_strlen(str_trimmed);
	free(str_trimmed);
}

void	process_dec(struct format  *format, va_list valist)
{

}

void	process_hex(struct format  *format, va_list valist)
{
	
}


void	process_conversions(char *str, int i, struct format *format, va_list valist)
{
	char	*test;
	char	conv;

	conv = str[i];
	if (conv == 's')
		process_str(format, valist);
	if (conv == 'd')
	{
	
	}
	if (conv == 'x')
	{
		/* code */
	}
	
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
			process_conversions(str, i, format, valist);
		}
		
	}
	return format->letter_count;
}

int main(int argc, char const *argv[])
{
	// int ret = ft_printf("123456789\n");
	int ret = printf("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	int ret2 = ft_printf("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	printf("ret : %d, ret2 : %d\n", ret, ret2);
	return 0;
}
