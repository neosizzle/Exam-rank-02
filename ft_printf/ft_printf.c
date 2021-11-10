#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct format 
{
	int	has_perc;
	int has_width;
	int	perc;
	int	width;
	int letter_count;
};

void	clear_format(struct format *format)
{
	format->has_perc = 0;
	format->has_width = 0;
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

int ft_numlen(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return 1;
	while (num != 0)
	{
		++i;
		num /= 10;
	}
	return i;
}

int ft_numlen_hex(unsigned int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return 1;
	while (num != 0)
	{
		++i;
		num /= 16;
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

void ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return;
	}
	if (n >= 0 && n <= 9)
	{
		ft_putchar(n + '0');
		return ;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(n * -1);
	}
}

char	*ft_strdup(char *str)
{
	char *res;
	int	i;

	res = (char *)malloc(sizeof(char) *( ft_strlen(str) + 1));
	i = -1;
	while (++i < ft_strlen(str))
		res[i] = str[i];
	res[i] = 0;
	return res;
}

char	*ft_addzero(char *str, int num, int idx)
{
	char	*res;
	int i;

	res = malloc(sizeof(char) * (ft_strlen(str) + num + 1));
	i = -1;
	if (idx == 1)
		res[0] = '-';
	while (++i < num)
		res[i + idx] = '0';
	if (idx == 1)
	{
		++i;
		++str;
	}
	while (*str)
	{
		res[i++] = *str;
		str++;
	}
	res[i] = 0;
	return res;
}

char	*ft_itoa_hex(unsigned int n)
{
	char	*res;
	char	*hex;
	int		len;
	int		offset;

	hex = "0123456789abcdef";
	len = ft_numlen_hex(n);
	res = malloc(sizeof (char) * (len + 1));
	offset = len - 1;
	while (offset >= 0)
	{
		res[offset] = hex[n % 16];
		n /= 16;
		--offset;
	}
	res[len] = 0;
	return res;
}

char	*ft_itoa(int n)
{
	char	*res;
	int		numlen;
	int		temp;
	int		offset;
	int		og_numlen;

	if (n == -2147483648)
	{
		res = ft_strdup("-2147483648");
		return res;
	}
	if (n == 0)
	{
		res = ft_strdup("0");
		return res;
	}
	numlen = 0;
	temp = n;
	offset = 0;
	if (n < 0)
		numlen++;
	while (temp)
	{
		temp /= 10;
		numlen++;
	}
	res = (char *)malloc(sizeof (char) * (numlen + 1));
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
		offset = 1;
	}
	og_numlen = numlen;
	while (numlen - 1 >= offset)
	{
		res[numlen - 1] = '0' + (n % 10);
		n /= 10;
		numlen--;
	}
	if (n < 0)
		res[0] = '-';
	res[og_numlen] = 0;
	return (res);
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
	// printf("res : %s\n", res);
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
	if (str[*i] >= '0' && str[*i] <= '9')
		format->has_width = 1;
	while (str[*i + offset] && str[*i + offset] <= '9' && str[*i + offset] >= '0')
	{
		offset++;
	}
	if (str[*i + offset] == '.')
	{
		format->has_perc = 1;
		format->perc = ft_atoi(str + *i + offset + 1);
	}
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
	if (format->perc > ft_strlen(str_raw) || format->has_perc == 0)
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
	int ltrcnt = format->letter_count;
	format->letter_count = ltrcnt + format->width + ft_strlen(str_trimmed);
	free(str_trimmed);
}

void	process_dec(struct format  *format, va_list valist)
{
	int		num;
	int		numlen_raw;
	char	*numstr_raw;
	char	*numstr_trimmed;

	num = va_arg(valist, int);

	//get numstr and raw numlen (without sign)
	numstr_raw = ft_itoa(num);
	numlen_raw = ft_numlen(num);
	// printf("numstr raw %s\n", numstr_raw);
	// printf("numlen raw %d\n", numlen_raw);

	//adjust for percision
	if (format->perc <= numlen_raw)
		format->perc = 0;
	else
		format->perc -= numlen_raw;

	//string is null when zero val widht and zero val percision
	//string is 0 when there is 0 value width
	//string is null when zero perc and zero value
	//add zeros 0th idx onwards if num is positive
	//add zeros 1st idx onwards if num is negative
	// if (num == 0 && format->has_perc && format->has_width && format->perc == 0 && format->width == 0)
	// 	numstr_trimmed = ft_strdup("");
	// else if (num == 0 && format->width == 0 && format->has_width && format->has_perc == 0)
	// 	numstr_trimmed = ft_strdup("0");
	// else if (num == 0 && format->perc == 0 && format->has_perc)
	// 	numstr_trimmed = ft_strdup("");
	// else if (num >= 0)
	// 	numstr_trimmed = ft_addzero(numstr_raw, format->perc, 0);
	// else
	// 	numstr_trimmed = ft_addzero(numstr_raw, format->perc, 1);
	if (num == 0 && format->has_perc && format->perc == 0)
		numstr_trimmed = ft_strdup("");
	else if (num >= 0)
		numstr_trimmed = ft_addzero(numstr_raw, format->perc, 0);
	else
		numstr_trimmed = ft_addzero(numstr_raw, format->perc, 1);

	//adjust for width
	format->width = format->width - ft_strlen(numstr_trimmed);
	if (format->width < 0)
		format->width = 0;
	print_spaces(format);

	//print numstr_trimmed w/ width and increment letters print
	//printf("numstr trimmed %s\n", numstr_trimmed);
	ft_putstr(numstr_trimmed);
	format->letter_count += format->width + ft_strlen(numstr_trimmed);
	free(numstr_trimmed);
	free(numstr_raw);
}

void	process_hex(struct format  *format, va_list valist)
{
	char			*hexstr_raw;
	char			*hexstr_trimmed;
	unsigned int	num;
	int				hexlen_raw;

	num = va_arg(valist, unsigned int);
	hexstr_raw = ft_itoa_hex(num);
	hexlen_raw = ft_numlen_hex(num);
	// printf("numstr raw %s\n", hexstr_raw);
	// printf("numlen raw %d\n", hexlen_raw);

	//adjust for percision
	if (format->perc <= hexlen_raw)
		format->perc = 0;
	else
		format->perc -= hexlen_raw;

	//if number is 0 and percision value is 0, string is ""
	//append leading zeros to the string
	if (num == 0 && format->has_perc && format->perc == 0)
		hexstr_trimmed = ft_strdup("");
	else
		hexstr_trimmed = ft_addzero(hexstr_raw, format->perc, 0);

	//adjust for width and print spaces
	if (format->width <= ft_strlen(hexstr_trimmed))
		format->width = 0;
	else
		format->width -= ft_strlen(hexstr_trimmed);
	print_spaces(format);

	//putstr and free, incremt letter cnt
	ft_putstr(hexstr_trimmed);
	format->letter_count += format->width + ft_strlen(hexstr_trimmed);
	free(hexstr_trimmed);
	free(hexstr_raw);
}

void	process_conversions(char *str, int i, struct format *format, va_list valist)
{
	char	conv;

	conv = str[i];
	if (conv == 's')
		process_str(format, valist);
	if (conv == 'd')
		process_dec(format, valist);
	if (conv == 'x')
		process_hex(format, valist);
	
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

#include <limits.h>
int main(int argc, char const *argv[])
{
	int ret = printf("s4p ~` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	int ret2 = ft_printf("s4p ~` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	printf("ret : %d, ret2 : %d\n", ret, ret2);
	return 0;
}
