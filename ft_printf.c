#include "ft_printf.h"

static	int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r'
			|| c == '\t' || c == '\v' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int		result;
	char	sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*(str)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*(str++) == '-')
			sign = -1;
	}
	while (*str != '\0' && ft_isdigit(*str))
	{
		if (result < 0)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		result = result * 10 + (*(str++) - '0');
	}
	return (result * (int)sign);
}

static  int    ft_init(t_flag *fl, size_t *len, char *str)
{
    if (str == NULL)
        return (1);
    fl->begin = 0;
    fl->len = 0;
    fl->min_len = 0;
    fl->sharp = 0;
    fl->sign = 0;
    len = 0;
}

int		ft_ter(char value, int a, int b)
{
	if (value)
		return (a);
	return (b);
}

int 	ft_isnum(char c)
{
	return ('0' <= c && c <= '9');
}

int		ft_check_flag(char c)
{
	if (c == '-' || c == '.' || c == '#' ||
		c == ' ' || c == '+' || ('0' <= c && c <= '9'))
		return (1);
	return (0);
}

size_t	ft_get_flag(char *str, t_flag *flag)
{
    size_t	i;

    i = 1;
    while (str[i] && ft_check_flag(str[i]))
    {
		flag->sharp = ft_ter(str[i] == '#', 1, flag->sharp);
		if (flag->sign != 2)
			flag->sign = ft_ter(str[i] == ' ', 1, flag->sign);
		flag->sign = ft_ter(str[i] == '+', 2, flag->sign);
		if (flag->begin != 2)
			flag->begin = ft_ter(str[i] == '0', 1, flag->sign);
		flag->begin = ft_ter(str[i] == '-', 2, flag->sign);
		if (str[i] != '0' && ft_isnum(str[i]))
			flag->min_len = ft_atoi(str, &i);
		else if (str[i] == '.')
			flag->len = ft_atoi(str, &(++i));
    	else
			i++;
	}
	return (i);
}

int 	ft_check_char(char c)
{
	if (c == 'd' || c == 'i')
		return (1);
	else if (c == 'u')
		return (2);
	else if (c == 'p')
		return (3);
	else if (c == 'c')
		return (4);
	else if (c == 's')
		return (5);
	else if (c == 'x')
		return (6);
	else if (c == 'X')
		return (7);
	else if (c == '%')
		return (8);
	return (0);
}

static  size_t ft_todo(t_flag *flag, int c, va_list arg)
{
	size_t len;

	if (c == 1)
		len = ft_char_d(flag, va_arg(arg, int));
	else if (c == 2)
		len = ft_char_u(flag, va_arg(arg, unsigned int));
	else if (c == 3)
		len = ft_char_p(flag, va_arg(arg, void *));
	else if (c == 4)
		len = ft_char_c(flag, va_arg(arg, char));
	else if (c == 5)
		len = ft_char_s(flag, va_arg(arg, char *));
	else if (c == 6)
		len = ft_char_x(flag, va_arg(arg, int));
	else if (c == 7)
		len = ft_char_X(flag, va_arg(arg, int));
	else if (c == 8)
		len = write(1, "%", 1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
    va_list	args;
    size_t	len;
    size_t	i;
    t_flag	flag;

    if (ft_init(&flag, &len, str))
        return (0);
    va_start(args, str);
    while (*str != '\0')
    {
        i = 0;
        while (str[i] != '%' || str[i] != '\0')
            i++;
        len += write(1, str, i);
        str += i;
        i = ft_get_flag(str, &flag);
        if (ft_check_char(str[i]))
            i += ft_todo(*flag, ft_check_char(str[i]));
        else
            str += write(1, str, i);
    }
    va_end(args);
    return (len);
}