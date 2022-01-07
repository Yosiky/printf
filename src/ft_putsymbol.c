/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsymbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:31:39 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/07 19:08:37 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != 0)
		len++;
	return (len);
}

int	ft_putchar(va_list data, __attribute__((unused)) flag_t *flag)
{
	char	c;

	c = va_arg(data, int);
	return (write(1, &c, 1));
}

int	ft_putstr(va_list data, __attribute__((unused)) flag_t *flag)
{
	char	*str;

	str = va_arg(data, char *);
	if (str == NULL)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	ft_putprecent(
	__attribute__((unused)) va_list data,
	__attribute__((unused)) flag_t *flag)
{
	return (write(1, "%", 1));
}
