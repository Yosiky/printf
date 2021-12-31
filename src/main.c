#include "ft_printf.h"

static int	ft_check_character(const char *c, va_list data)
{
	static const char	buff[] = "cspdiuxX%";
	static int			(*func[])(va_list) = {
		ft_putchar, ft_putstr, ft_putadd,
		ft_putdigit, ft_putdigit, ft_putudigit,
		ft_puthex_lower, ft_puthex_upper, ft_putprecent
	};
	size_t				len;

	len = 0;
	while (buff[len])
	{
		if (*c != buff[len])
			len++;
		else
			return (func[len](data));
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	data;
	int		count;
	int		i;

	va_start(data, str);
	count = 0;
	i = 0;
	if (str != NULL)
	{
		while (str[i] != 0)
		{
			if (str[i] == '%')
				count += ft_check_character(str + (++i), data);
			else
			{
				count++;
				write(1, str + i, 1);
			}
			i++;
		}
	}
	va_end(data);
	return (count);
}
