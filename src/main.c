/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:57 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/10 16:41:58 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_character(char *str, int *i, va_list data)
{
	static const char	buff[] = "cspdiuxX%";
	static int			(*func[])(va_list, t_flag *) = {
		ft_putchar, ft_putstr, ft_putadd, ft_putdigit, ft_putdigit,
		ft_putudigit, ft_puthex_lower, ft_puthex_upper, ft_putprecent};
	size_t				len;
	t_flag				flag;

	len = 0;
	ft_flag_init(&flag);
	ft_check_flag(str, i, &flag);
	ft_check_t_flag(&flag, data, str, i);
	while (buff[len])
	{
		if (str[*i] != buff[len])
			len++;
		else
		{
			++(*i);
			return (func[len](data, &flag));
		}
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	data;
	int		count;
	int		i;

	va_start(data, str);
	count = 0;
	i = 0;
	if (str != NULL)
	{
		while (str[i] != 0)
		{
			if (str[i++] == '%')
				count += ft_check_character((char *)str, &i, data);
			else
			{
				count++;
				write(1, str + i - 1, 1);
			}
		}
	}
	va_end(data);
	return (count);
}
