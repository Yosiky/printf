/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:24 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/08 14:56:23 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	buff[0] = hex[15];
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

static int	ft_func_one(t_flag *flag, int f1, int f2)
{
	int	len;

	len = 0;
	if (!f1 && flag->minus_zero == '0' && flag->sharp)
	{
		if (f2 == 'f')
			len += write(1, "0x", 2);
		else
			len += write(1, "0X", 2);
	}
	while (flag->widht > 0)
	{
		len++;
		write(1, &(flag->minus_zero), 1);
		flag->widht--;
	}
	if (!f1 && flag->minus_zero == ' ' && flag->sharp)
	{
		if (f2 == 'f')
			len += write(1, "0x", 2);
		else
			len += write(1, "0X", 2);
	}
	return (len);
}

static int	ft_max(int a, int b, int c)
{
	if (c)
	{
		if (a > b)
			return (a);
		return (b);
	}
	return (a);
}

static int	ft_check_flag(t_flag *flag, int count, int f1, char f2)
{
	int	len;

	len = 0;
	flag->widht -= 2 * flag->sharp;
	flag->widht -= ft_max(count, flag->precision, flag->flag_p);
	if (flag->minus_zero != '-')
		len += ft_func_one(flag, f1, f2);
	else if (flag->sharp && !f1)
	{
		if (f2 == 'f')
			len += write(1, "0x", 2);
		else
			len += write(1, "0X", 2);
	}		
	while (flag->precision > count)
	{
		flag->precision--;
		len++;
		write(1, "0", 1);
	}
	return (len);
}

int	ft_puthex_lower(va_list data, t_flag *flag)
{
	int		len;
	int		count;
	char	buff[12];

	len = ft_dectohex(buff, 12, va_arg(data, int), 0);
	count = ft_check_flag(flag, len, len == 1 && buff[11] == '0', buff[0]);
	if (!(flag->flag_p && flag->precision == 0 && len == 1 && buff[11] == '0'))
		write(1, buff + 12 - len, len);
	else
	{
		flag->widht++;
		len = 0;
	}
	while (flag->widht > 0)
	{
		len += write(1, " ", 1);
		flag->widht--;
	}
	return (count + len);
}

int	ft_puthex_upper(va_list data, t_flag *flag)
{
	int		len;
	int		count;
	char	buff[12];

	len = ft_dectohex(buff, 12, va_arg(data, int), 1);
	count = ft_check_flag(flag, len, len == 1 && buff[11] == '0', buff[0]);
	if (!(flag->flag_p && flag->precision == 0 && len == 1 && buff[11] == '0'))
		write(1, buff + 12 - len, len);
	else
	{
		flag->widht++;
		len = 0;
	}
	while (flag->widht > 0)
	{
		len += write(1, " ", 1);
		flag->widht--;
	}
	return (count + len);
}

static int	ft_add_print(t_flag *flag, int f1)
{
	int	len;

	len = 0;
	if (f1)
		len += write(1, "-", 1);
	else if (flag->plus_space)
		len += write(1, &(flag->plus_space), 1);
	return (len + write(1, "0x", 2));
}

static int	ft_func_two(t_flag *flag, int f1)
{
	int	len;

	len = 0;
	if (flag->minus_zero == '0')
	{
		if (f1)
			flag->minus_zero = ' ';
		else
			len += ft_add_print(flag, 0);
	}
	while (flag->minus_zero != '-' && flag->widht > 0)
	{
		len++;
		write(1, &(flag->minus_zero), 1);
		flag->widht--;
	}
	if (!f1 && (flag->minus_zero == ' ' || flag->minus_zero == '-'))
		len += ft_add_print(flag, 0);
	return (len);
}

static int	ft_check_flag_add(t_flag *flag, int count, int f1)
{
	int		len;
	char	buff;

	len = 0;
	if (f1)
		buff = ' ';
	else
		buff = '0';
	flag->widht -= !f1 * flag->plus_space + f1 * 5 + !f1 * 2;
	flag->widht -= !f1 * ft_max(count, flag->precision, flag->flag_p);
	len += ft_func_two(flag, f1);
	while (flag->precision > count)
	{
		flag->precision--;
		len++;
		write(1, &buff, 1);
	}
	return (len);
}

int	ft_putadd(va_list data, t_flag *flag)
{
	char	buff[20];
	int		count;
	size_t	value;
	int		f;

	value = (size_t)va_arg(data, void *);
	count = ft_dectohex_p(buff, 17, value);
	f = ft_check_flag_add(flag, count, value == 0);
	if (value == 0)
		write(1, "(nil)", 5);
	else
		f += write(1, buff + 17 - count, count);
	while (flag->widht > 0)
	{
		f += write(1, " ", 1);
		flag->widht--;
	}
	return (f + 5 * (value == 0));
}
