/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:15:31 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/10 16:42:04 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flag_init(t_flag *flag)
{
	flag->flag_w = 0;
	flag->flag_p = 0;
	flag->sharp = 0;
	flag->widht = 0;
	flag->precision = 0;
	flag->minus_zero = ' ';
	flag->plus_space = 0;
}

void	ft_check_flag( char *str, int *i, t_flag *flag)
{
	while (ft_check_char(str[*i]))
	{
		if (str[*i] == '#')
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

void	ft_check_t_flag(t_flag *flag, va_list data, const char *c, int *i)
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
