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

	len = ft_strlen(v);
	write(1, v, len);
	return (len);
}

size_t	ft_char_c(char v)
{
	write(1, &v, 1);
	return (1);
}

size_t	ft_dectohex(size_t v, char *res, char flag)
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

	len = 0;
	flag = 0;
	if (v < 0)
	{
		flag = 1;
		write(1, "-", 1);
	}
	while (v)
	{
		res[10 - (len++)] = '0' + v % 10;
		v /= 10;
	}
	write(1, res + 10 - len, len);
	return (len + flag);
}

size_t	ft_char_u(unsigned int v)
{
	size_t	len;
	char	flag;
	char	res[11];

	len = 0;
	while (v)
	{
		res[10 - (len++)] = '0' + v % 10;
		v /= 10;
	}
	write(1, res + 10 - len, len);
	return (len);
}

size_t	ft_char_p(size_t v)
{
	size_t	len;
	char	res[17];

	len = ft_dectohex(v, res, 0);
	write(1, "0x", 2);
	write(1, res + 16 - len, len);
	return (len + 2);
}

size_t	ft_char_x(size_t v)
{
	size_t	len;
	char	res[17];

	len = ft_dectohex(v, res, 0);
	write(1, res + 16 - len, len);
	return (len);
}

size_t	ft_char_X(size_t v)
{
	size_t	len;
	char	res[17];

	len = ft_dectohex(v, res, 1);
	write(1, res + 16 - len, len);
	return (len);
}

static	int		ft_choose(const char *str, size_t *len, va_list *v)
{
	if (*(str + 1) == 's')
		ft_char_s(va_arg(*v, char *));
	else if (*(str + 1) == 'c')
		ft_char_c(va_arg(*v, int));
	else if (*(str + 1) == 'd')
		ft_char_d(va_arg(*v, int));
	else if (*(str + 1) == 'p')
		ft_char_p((size_t)va_arg(*v, void *));
	else if (*(str + 1) == 'i')
		ft_char_d(va_arg(*v, int));
	else if (*(str + 1) == 'u')
		ft_char_u(va_arg(*v, unsigned int));
	else if (*(str + 1) == 'x')
		ft_char_x(va_arg(*v, int)); // ?
	else if (*(str + 1) == 'X')
		ft_char_X(va_arg(*v, int));
	*len += 1;
}

static	int		ft_check(const char *str)
{
	if (*str == '%' && (*(str + 1) == 'c' || *(str + 1) == 's'
		|| *(str + 1) == 'p' || *(str + 1) == 'd'
		|| *(str + 1) == 'i' || *(str + 1) == 'u'
		|| *(str + 1) == 'x' || *(str + 1) == 'X'
		|| *(str + 1) == '%'))
		return (1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	len;

	len = 0;
	va_start(args, str);
	while (str[len] != '\0')
	{
		if (ft_check(str + len))
			ft_choose(str, &len, &args);
		else	
		{
			write(1, str, 1);
			len++;
		}
	}
	va_end(args);
	return (len);
}
