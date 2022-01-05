/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:10 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/05 22:21:26 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
static void	ft_init(char *str, int value)
{
	if (value < 0)
		str[0] = '-';
	else if (value == 0)
		str[0] = '0';
}*/

static int	check_flag(int flag, long long *value)
{
	char	f[2];

	f[0] = ' ';
	f[1] = '+';
	if (flag == 2 || flag == 3)
	{
		if (*value > 0)
			return (write(1, f + flag - 2, 1));
		else if (*value == 0)
			return (write(1, f + flag - 2, 1) + write(1, "0", 1));
		else
		{
			*value *= -1;
			return (write(1, "-", 1));
		}
	}
	if (*value < 0)
	{
		*value *= -1;
		return (write(1, "-", 1));
	}
	return (0);
}

int	ft_putdigit(va_list data, int flag)
{
	long long	value;
	int			count;
	int			f;
	char		buff[12];

	count = 0;
	value = va_arg(data, int);
	f = check_flag(flag, &value);
	while (value)
	{
		buff[11 - count] = '0' + value % 10;
		count++;
		value /= 10;
	}
	write(1, buff + 12 - count, count);
	return (count + f);
}

static int	check_flag_u(int flag)
{
	if (flag == 2)
		return (write(1, " ", 1));
	else if (flag == 3)
		return (write(1, "+", 1));
	return (0);
}

int	ft_putudigit(va_list data, int flag)
{
	unsigned int	value;
	int				count;
	char			buff[12];
	int				f;

	count = 0;
	value = va_arg(data, int);
	f = check_flag_u(flag);
	if (value == 0)
	{
		buff[11] = '0';
		count = 1;
	}
	while (value)
	{
		buff[11 - count] = '0' + value % 10;
		count++;
		value /= 10;
	}
	write(1, buff + 12 - count, count);
	return (count + f);
}
