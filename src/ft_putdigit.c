/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:10 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/10 16:48:17 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_flag_extension_one(t_flag *flag, int f1)
{
	int	len;

	len = 0;
	if (flag->minus_zero == '0')
	{
		if (f1)
			len += write(1, "-", 1);
		else if (flag->plus_space)
			len += write(1, &(flag->plus_space), 1);
	}
	while (flag->widht > 0)
	{
		len++;
		write(1, &(flag->minus_zero), 1);
		flag->widht--;
	}
	if (flag->minus_zero == ' ')
	{
		if (f1)
			len += write(1, "-", 1);
		else if (flag->plus_space)
			len += write(1, &(flag->plus_space), 1);
	}
	return (len);
}

static int	ft_check_flag_d(t_flag *flag, int count, int f1)
{
	int	len;

	len = 0;
	flag->widht -= (f1 || flag->plus_space);
	flag->widht -= ft_max(count, flag->precision, flag->flag_p);
	if (flag->minus_zero != '-')
		len += ft_check_flag_extension_one(flag, f1);
	else if (f1)
		len += write(1, "-", 1);
	while (flag->precision > count)
	{
		flag->precision--;
		len++;
		write(1, "0", 1);
	}
	return (len);
}

static int	ft_itoa(char *buff, long long value, int flag)
{
	int	count;

	count = 0;
	if (flag && value < 0)
		value *= -1;
	else if (value == 0)
	{
		buff[11] = '0';
		return (1);
	}
	while (value)
	{
		buff[11 - count] = '0' + value % 10;
		count++;
		value /= 10;
	}
	return (count);
}

int	ft_putdigit(va_list data, t_flag *flag)
{
	int		value;
	int		count;
	int		f;
	char	buff[12];

	value = va_arg(data, int);
	count = ft_itoa(buff, value, 1);
	f = ft_check_flag_d(flag, count, value < 0);
	if (!(flag->flag_p && flag->precision == 0 && value == 0))
		write(1, buff + 12 - count, count);
	else
	{
		flag->widht++;
		count = 0;
	}
	while (flag->widht > 0)
	{
		f += write(1, " ", 1);
		flag->widht--;
	}
	return (count + f);
}

int	ft_putudigit(va_list data, t_flag *flag)
{
	unsigned int	value;
	int				count;
	int				f;
	char			buff[12];

	flag->plus_space = 0;
	value = va_arg(data, int);
	count = ft_itoa(buff, value, 0);
	f = ft_check_flag_d(flag, count, 0);
	if (!(flag->flag_p && flag->precision == 0 && value == 0))
		write(1, buff + 12 - count, count);
	else
	{
		flag->widht++;
		count = 0;
	}
	while (flag->widht > 0)
	{
		f += write(1, " ", 1);
		flag->widht--;
	}
	return (count + f);
}
