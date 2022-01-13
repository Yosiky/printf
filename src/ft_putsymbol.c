/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsymbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:39 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/10 16:42:16 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_flag_c(t_flag *flag)
{
	int	len;

	len = 0;
	flag->widht -= 1;
	if (flag->minus_zero != '-')
	{
		while (flag->widht > 0)
		{
			write(1, " ", 1);
			flag->widht--;
			len++;
		}
	}
	return (len);
}

int	ft_putchar(va_list data, t_flag *flag)
{
	char	c;
	int		len;

	c = va_arg(data, int);
	len = ft_check_flag_c(flag);
	len += write(1, &c, 1);
	while (flag->minus_zero == '-' && flag->widht > 0)
	{
		flag->widht--;
		len += write(1, " ", 1);
	}
	return (len);
}

static int	ft_check_flag_s(t_flag *flag, int *count)
{
	int	len;

	len = 0;
	if ((flag->flag_p) && (flag->precision < *count))
		*count = flag->precision;
	flag->widht -= *count;
	if (flag->minus_zero != '-')
	{
		while (flag->widht > 0)
		{
			write(1, " ", 1);
			flag->widht--;
			len++;
		}
	}	
	return (len);
}

int	ft_putstr(va_list data, t_flag *flag)
{
	char	*str;
	int		len;
	int		slen;

	str = va_arg(data, char *);
	if (str == NULL)
		str = "(null)";
	slen = ft_strlen(str);
	len = ft_check_flag_s(flag, &slen);
	len += write(1, str, slen);
	while (flag->minus_zero == '-' && flag->widht > 0)
	{
		flag->widht--;
		len += write(1, " ", 1);
	}
	return (len);
}

int	ft_putprecent(
	__attribute__((unused)) va_list data,
	__attribute__((unused)) t_flag *flag)
{
	return (write(1, "%", 1));
}
