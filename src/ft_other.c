/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:40:01 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/10 16:47:39 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_char(char c)
{
	return (c == '-' || c == '#' || c == ' ' || c == '+' || c == '*'
		|| ('0' <= c && c <= '9'));
}

int	ft_isnum(char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len] != 0)
		len++;
	return (len);
}

int	ft_atoi(const char *c, int *i, int flag)
{
	int	value;

	value = 0;
	if (flag)
		++(*i);
	while (ft_isnum(c[*i]))
	{
		value = value * 10 + (c[*i] - '0');
		++(*i);
	}
	return (value);
}

int	ft_max(int a, int b, int c)
{
	if (c)
	{
		if (a > b)
			return (a);
		return (b);
	}
	return (a);
}
