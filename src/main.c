/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosiky <yosiky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:57 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/05 21:41:00 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_flag(const char **c, int *i)
{
	while (**c == '#' || **c == ' ' || **c == '+')
	{
		(*c)++;
		(*i)++;
	}
	if ((*(*c - 1)) == '#')
		return (1);
	else if ((*(*c - 1)) == ' ')
		return (2);
	else if ((*(*c - 1)) == '+')
		return (3);
	return (0);
}

static int	ft_check_character(const char *c, va_list data, int *i)
{
	static const char	buff[] = "cspdiuxX%";
	static int			(*func[])(va_list, int) = {
		ft_putchar, ft_putstr, ft_putadd,
		ft_putdigit, ft_putdigit, ft_putudigit,
		ft_puthex_lower, ft_puthex_upper, ft_putprecent
	};
	size_t				len;
	int					flag;

	flag = check_flag(&c, i);
	len = 0;
	while (buff[len])
	{
		if (*c != buff[len])
			len++;
		else
		{
			(*i)++;
			return (func[len](data, flag));
		}
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
				count += ft_check_character(str + (++i), data, &i);
			else
			{
				count++;
				write(1, str + (i++), 1);
			}
		}
	}
	va_end(data);
	return (count);
}
