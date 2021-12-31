#include "ft_printf.h"

static int	ft_dectohex_p(char *buff, size_t l, size_t value)
{
	const char	*hex = "0123456789abcdef";
	int			len;

	len = 0;
	while (value)
	{
		buff[l - 1 - (len++)] = hex[value % 16];
		value /= 16;
	}
	return (len);
}

static int	ft_dectohex(char *buff, size_t l, unsigned int value, int flag)
{
	const char	*hex_lower = "0123456789abcdef";
	const char	*hex_upper = "0123456789ABCDEF";
	char		*hex;
	int			len;

	if (flag)
		hex = (char *)hex_upper;
	else
		hex = (char *)hex_lower;
	len = 0;
	if (value == 0)
	{
		buff[l - 1] = '0';
		len = 1;
	}
	while (value)
	{
		buff[l - 1 - (len++)] = hex[value % 16];
		value /= 16;
	}
	return (len);
}

int	ft_puthex_lower(va_list data)
{
	int		len;
	char	buff[12];

	len = ft_dectohex(buff, 12, va_arg(data, int), 0);
	return (write(1, buff + 12 - len, len));
}

int	ft_puthex_upper(va_list data)
{
	int		len;
	char	buff[12];

	len = ft_dectohex(buff, 12, va_arg(data, int), 1);
	return (write(1, buff + 12 - len, len));
}

int	ft_putadd(va_list data)
{
	char	buff[20];
	int		count;
	size_t	value;

	value = (size_t)va_arg(data, void *);
	if (value == 0)
		write(1, "(nil)", 5);
	else
	{
		write(1, "0x", 2);
		count = ft_dectohex_p(buff, 17, value);
		return (2 + write(1, buff + 17 - count, count));
	}
}