/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:10 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/07 19:28:56 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_flag(flag_t *flag, long long *value)
{
	if (*value < 0)
	{
		*value *= -1;
		return (write(1, "-", 1));
	}
	if (flag->plus)
	{
		if (*value == 0)
			return (write(1, "+0", 2));
		else
			return (write(1, "+", 1));
	}
	else if (flag->space)
	{
		if (*value == 0)
			return (write(1, " 0", 2));
		else
			return (write(1, " ", 1));
	}
	if (*value == 0)
		return (write(1, "0", 1));
	return (0);
}

int	ft_putdigit(va_list data, flag_t *flag)
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

int	ft_putudigit(va_list data, __attribute((unused)) flag_t *flag)
{
	unsigned int	value;
	int				count;
	char			buff[12];

	count = 0;
	value = va_arg(data, int);
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
	return (count);
}
