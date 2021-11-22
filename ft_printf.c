#include "ft_printf.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_char_s(char *v)
{
	size_t	len;

	if (v == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(v);
	write(1, v, len);
	return (len);
}

size_t	ft_char_c(char v)
{
	write(1, &v, 1);
	return (1);
}

size_t	ft_dectohex(unsigned int v, char *res, char flag)
{
	const char	base_upper[] = "0123456789ABCDEF";
	const char	base_lower[] = "0123456789abcdef";
	char		*base;
	size_t		len;
	
	if (flag)
		base = (char *)base_upper;
	else
		base = (char *)base_lower;
	len = 0;
	while (v)
	{
		res[16 - (len++)] = base[v % 16];
		v /= 16;
	}
	return (len);
}

size_t	ft_dectohex_p(size_t v, char *res, char flag)
{
	const char	base_upper[] = "0123456789ABCDEF";
	const char	base_lower[] = "0123456789abcdef";
	char		*base;
	size_t		len;

	if (flag)
		base = (char *)base_upper;
	else
		base = (char *)base_lower;
	len = 0;
	while (v)
	{
		res[16 - (len++)] = base[v % 16];
		v /= 16;
	}
	return (len);
}

size_t	ft_char_d(int v)
{
	size_t	len;
	char	flag;
	char	res[11];
	size_t  value;

	if (v == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	len = 0;
	flag = 0;
	value = v;
	if (v < 0)
	{
		value *= -1;
		flag = 1;
		write(1, "-", 1);
	}
	while (value)
	{
		res[10 - (len++)] = '0' + value % 10;
		value /= 10;
	}
	write(1, res + 11 - len, len);
	return (len + flag);
}

size_t	ft_char_u(unsigned int v)
{
	size_t	len;
	char	res[11];

	len = 0;
	if (v == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (v)
	{
		res[10 - (len++)] = '0' + v % 10;
		v /= 10;
	}
	write(1, res + 11 - len, len);
	return (len);
}

size_t	ft_char_p(size_t v)
{
	size_t	len;
	char	res[17];

	if (v == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	len = ft_dectohex_p(v, res, 0);
	write(1, "0x", 2);
	write(1, res + 17 - len, len);
	return (len + 2);
}

size_t	ft_char_x(size_t v)
{
	size_t	len;
	char	res[17];

	if (v == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	len = ft_dectohex(v, res, 0);
	write(1, res + 17 - len, len);
	return (len);
}

size_t	ft_char_X(size_t v)
{
	size_t	len;
	char	res[17];

	if (v == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	len = ft_dectohex(v, res, 1);
	write(1, res + 17 - len, len);
	return (len);
}

size_t	ft_char_proc(void)
{
	write(1, "%", 1);
	return (1);
}

static	void	ft_choose(const char *str, size_t *len, va_list *v)
{
	if (*(str + 1) == 's')
		*len += ft_char_s(va_arg(*v, char *));
	else if (*(str + 1) == 'c')
		*len += ft_char_c(va_arg(*v, int));
	else if (*(str + 1) == 'd')
		*len += ft_char_d(va_arg(*v, int));
	else if (*(str + 1) == 'p')
		*len += ft_char_p((size_t)va_arg(*v, void *));
	else if (*(str + 1) == 'i')
		*len += ft_char_d(va_arg(*v, int));
	else if (*(str + 1) == 'u')
		*len += ft_char_u(va_arg(*v, unsigned int));
	else if (*(str + 1) == 'x')
		*len += ft_char_x(va_arg(*v, int)); // ?
	else if (*(str + 1) == 'X')
		*len += ft_char_X(va_arg(*v, int));
	else if (*(str + 1) == '%')
		*len += ft_char_proc();
}

static	int		ft_check_spec(const char str)
{
	if (str == '\0')
		return (-1);
	else if (str == '%')
		return (1);
	else if (str == 'c' || str == 's')
		return (2);
	else if (str == 'p' || str == 'd' || str == 'i')
		return (3);
	else if (str == 'u')
		return (4);
	else if (str == 'x')
		return (5);
	else if (str == 'X')
		return (6);
	return (0);
}

static	int		ft_check_flag(const char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else if (c == '-')
		return (2);
	else if (c == '.')
		return (3);
	else if (c == '#')
		return (4);
	else if (c == ' ')
		return (5);
	else if (c == '+')
		return (6);
	return (0);
}

size_t	ft_flags(char **str, va_list args)
{
	size_t	i;
	size_t	len;
	t_flag	check;

	check = {};
	i = 0;
	while (!ft_check((*str)[i]) && ft_check_flag((*str)[i]))
		i++;
	if (!ft_check_flag((*str)[i]) || (*str)[i] == '\0' || (*str)[i] == '%')
	{
		len = write(1, "%", 1);
		i = 1;
	}
	else
	{
	}
	str += i;
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	len;
	size_t	count;

	len = 0;
	va_start(args, str);
	while (*str != '\0')
	{
		count = 0;
		while (str[count] != '%' && str[count] != '\0')
			count++;
		write(1, str, count);
		str += count;
		len += count;
		len += ft_flags(&(++str), args);
	}
	va_end(args);
	return (len);
}
