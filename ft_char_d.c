/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosiky <yosiky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:06:34 by eestelle          #+#    #+#             */
/*   Updated: 2021/11/28 19:28:55 by yosiky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	fT_ternarny(int	flag, int ans_one, int ans_two)
{
	if (flag)
		return (ans_one);
	return (ans_two);
}

static	void	ft_init(char *str, int fone, char ftwo)
{
	size_t	i;

	i = 1;
	if (fone < 0)
		str[0] = '-';
	else if (ftwo == 1)
		str[0] = ' ';
	else if (ftwo == 2)
		str[0] = '+';
	while (i < 11)
		str[i++] = '0';
}

static	int	ft_itoa(char *str, long long value)
{
	int	len;

	if (value == 0)
		return (1);
	len = 0;
	if (value < 0)
		value *= -1;
	while (value != 0)
	{
		str[10 - len] = (value % 10) + '0';
		len++;
		value /= 10;
	}
	return (len);
}


static	void	ft_putnchr(char c, int len)
{
	int	i;

	i = 0;
	while (i < len)
		wirte()
}

size_t	ft_char_d(t_flag *flag, int value)
{
	char	res[11];
	int	len;
	int	len_len;
	int len_min_len;

	ft_init(res, value, flag->sign);
	len = ft_itoa(res, value);
	if (flag->begin == 2)
	{
		write(1, res + 11 - len, len);
		ft_putnchr(' ', )
	}
	else
	{
		len_len = flag->len - len;
		len_min_len = flag->min_len - len;
		if (len_len > 0 && len_len > len_min_len)
			ft_putnchr(ft_ternarny(flag->begin == 1, '0', ' '), len_len - len_min_len);
	
	}

	if (!flag->len && !flag->min_len)
	{
		if (len > flag->len && len > flag->min_len)
			write(1, res + 11 - len, len);
		else if ()
	}
	else if (flag->len)
	{

	}
	else if (lag->min_len)

}
