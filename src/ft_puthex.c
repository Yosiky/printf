/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:24 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/10 16:52:01 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static int	ft_check_flag_h(t_flag *flag, int count, int f1, char f2)
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
	count = ft_check_flag_h(flag, len, len == 1 && buff[11] == '0', buff[0]);
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
	count = ft_check_flag_h(flag, len, len == 1 && buff[11] == '0', buff[0]);
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
