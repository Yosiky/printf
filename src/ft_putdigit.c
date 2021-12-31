/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:10 by eestelle          #+#    #+#             */
/*   Updated: 2021/12/31 21:31:11 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_init(char *str, int value)
{
	if (value < 0)
		str[0] = '-';
	else if (value == 0)
		str[0] = '0';
}

int	ft_putdigit(va_list data)
{
	long long	value;
	int			count;
	int			flag;
	char		buff[12];

	count = 0;
	flag = 0;
	value = va_arg(data, int);
	ft_init(buff, value);
	if (value == 0 || value < 0)
	{
		value *= -1;
		flag = 1;
	}
	while (value)
	{
		buff[11 - count] = '0' + value % 10;
		count++;
		value /= 10;
	}
	write(1, buff, flag);
	write(1, buff + 12 - count, count);
	return (count + flag);
}

int	ft_putudigit(va_list data)
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
