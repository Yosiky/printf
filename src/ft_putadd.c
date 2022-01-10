/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:50:34 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/10 16:52:35 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_dectohex(char *buff, size_t l, size_t value)
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
	count = ft_dectohex(buff, 17, value);
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
