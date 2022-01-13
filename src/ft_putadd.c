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
	if (value == 0)
	{
		len = 1;
		buff[l - 1] = '0';
	}
	while (value)
	{
		buff[l - 1 - (len++)] = hex[value % 16];
		value /= 16;
	}
	return (len);
}

static int	ft_func_two(t_flag *flag)
{
	int	len;

	len = 0;
	if (flag->minus_zero == '0' && flag->plus_space)
		len += write(1, &(flag->plus_space), 1) + write(1, "0x", 2);
	while (flag->minus_zero != '-' && flag->widht > 0)
	{
		len++;
		write(1, &(flag->minus_zero), 1);
		flag->widht--;
	}
	if (flag->minus_zero == ' ' || flag->minus_zero == '-')
	{
		if (flag->plus_space)
			len += write(1, &(flag->plus_space), 1);
		len += write(1, "0x", 2);
	}
	return (len);
}

static int	ft_check_flag_add(t_flag *flag, int count)
{
	int		len;
	char	buff;

	len = 0;
	buff = '0';
	flag->widht -= flag->plus_space + 2;
	flag->widht -= ft_max(count, flag->precision, flag->flag_p);
	len += ft_func_two(flag);
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
	f = ft_check_flag_add(flag, count);
	f += write(1, buff + 17 - count, count);
	while (flag->widht > 0)
	{
		f += write(1, " ", 1);
		flag->widht--;
	}
	return (f);
}
