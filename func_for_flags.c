#include "ft_printf.h"

static	int	ft_isdigit(const char c)
{
	return ('0' <= c && c <= '9');
}

static	int	ft_atoi(const char *str, size_t *i)
{
	int		result;

	result = 0;
	while (ft_isdigit(str[*i]))
	{
		result = result * 10 + str[(*i)++] - '0';
	}
	--(*i);
	return (result);
}


static	int		ft_check_flag(char c)
{
	if (c == '-' || c == '.' || c == '#' ||
	    c == ' ' || c == '+' || ('0' <= c && c <= '9'))
		return (1);
	return (0);
}



size_t	ft_get_flag(const char *str, t_flag *flag)
{
	size_t	i;

	i = 1;
	while (ft_check_flag(str[i]))
	{
		if (str[i] == '#')
			flag->sharp = 1;
		else if (flag->sign != 2 && str[i] == ' ')
			flag->sign = 1;
		else if (str[i] == '+')
			flag->sign = 2;
		else if (flag->begin != 2 && str[i] == '0')
			flag->begin = 1;
		else if (str[i] == '-')
			flag->begin = 2;
		else if ('0' < str[i] && str[i] <= '9')
			flag->min_len = ft_atoi(str, &i);
		else if (str[i] == '.')
		{
			++i;
			flag->len = ft_atoi(str, &i);
		}
		++i;
	}
	return (i);
}
