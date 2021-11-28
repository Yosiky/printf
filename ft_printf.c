#include "ft_printf.h"

static  int    ft_init(t_flag *fl, size_t *len, const char *str)
{
    if (str == NULL)
        return (1);
    fl->begin = 0;
    fl->len = 0;
    fl->min_len = 0;
    fl->sharp = 0;
    fl->sign = 0;
    len = 0;
	return (0);
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
	if (c == 1)
		return (t_char_d(flag, va_arg(arg, int)));
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
		return (write(1, "%", 1));
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
        while (str[i] != '%' && str[i] != '\0')
            ++i;
        len += write(1, str, i);
	    if (str[i] == '\0')
		    break ;
        str += i;
        i = ft_get_flag(str, &flag);
		if (ft_check_char(str[i]))
            str += i + ft_todo(&flag, args);
        else
            str += write(1, str, i);

	}
    va_end(args);
    return (len);
}
