/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:57 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/08 02:30:00 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_char(char c)
{
	return (c == '-' || c == '#' || c == ' ' || c == '+' || c == '*' ||
		('0' <= c && c <= '9'));
}

static int  ft_isnum(char c)
{
	return ('0' <= c && c <= '9');
}

int ft_atoi(const char *c, int *i, int flag)
{
	int value;

	value = 0;
	if (flag)
		++(*i);
	while (ft_isnum(c[*i]))
	{
		value = value * 10 + (c[*i] - '0');
		++(*i);
	}
	return (value);
}

void	check_t_flag(t_flag *flag, va_list data, const char *c, int *i)
{
	if (flag->flag_w)
	{
		if (flag->widht == 0)
			flag->widht = va_arg(data, int);
		if (flag->widht < 0)
			flag->flag_w = 0;
	}
	if (c[*i] == '.')
	{
		flag->flag_p = 1;
		++(*i);
		if (c[*i] == '*')
		{
			++(*i);
			flag->precision = va_arg(data, int);
		}
		else
			flag->precision = ft_atoi(c, i, 0);
		if (flag->precision < 0)
			flag->precision = 0;
		if (flag->minus_zero == '0')
			flag->minus_zero = ' ';
	}
}



/*
static int	ft_check_character(char *str)
{
	static const char	buff[] = "cspdiuxX%";
	static int			(*func[])(va_list, t_flag *) = {
		ft_putchar, ft_putstr, ft_putadd, ft_putdigit, ft_putdigit,
		ft_putudigit, ft_puthex_lower, ft_puthex_upper, ft_putprecent};
	size_t				len;
	t_flag				flag;

	len = 0;
	flag_init(&flag);
	check_flag(&c, i, &flag, data);
	check_t_flag(&flag, data, &c, i);
	while (buff[len])
	{
		if (*c != buff[len])
			len++;
		else
		{
			++(*i);
			return (func[len](data, &flag));
		}
	}
	return (0);
}*/

void    flag_init(t_flag *flag)
{
	flag->flag_w = 0;
	flag->flag_p = 0;
	flag->sharp = 0;
	flag->widht = 0;
	flag->precision = 0;
	flag->minus_zero = ' ';
	flag->plus_space = 0;
}

static void	check_flag( char *str, int *i, t_flag *flag)
{
	while (check_char(str[*i]))
	{
		if (str[*i - 1] == '#')
			flag->sharp = 1;
		else if (str[*i] == '+')
			flag->plus_space = '+';
		else if (str[*i] == ' ')
			flag->plus_space = ' ';
		else if (str[*i] == '-')
			flag->minus_zero = '-';
		else if (str[*i] == '0')
			flag->minus_zero = '0';
		else if (ft_isnum(str[*i]) || (str[*i] == '*' && !flag->widht))
			flag->flag_w = 1;
		if (ft_isnum(str[*i]) && str[*i] != '0')
			flag->widht = ft_atoi(str, i, 0);
		else
			++(*i);
	}
}

int	ft_check_character(char *str, int *i, va_list data)
{
	static const char	buff[] = "cspdiuxX%";
	static int			(*func[])(va_list, t_flag *) = {
		ft_putchar, ft_putstr, ft_putadd, ft_putdigit, ft_putdigit,
		ft_putudigit, ft_puthex_lower, ft_puthex_upper, ft_putprecent};
	size_t				len;
	t_flag				flag;

	len = 0;
	flag_init(&flag);
	check_flag(str, i, &flag);
	check_t_flag(&flag, data, str, i);
	while (buff[len])
	{
		if (str[*i] != buff[len])
			len++;
		else
		{
			++(*i);
			return (func[len](data, &flag));
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
			if (str[i++] == '%')
				count += ft_check_character((char *)str, &i, data);
			else
			{
				count++;
				write(1, str + i - 1, 1);
			}
		}
	}
	va_end(data);
	return (count);
}
