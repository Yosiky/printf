/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:30:50 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/07 19:23:56 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct	flag_s
{
	int	sharp;
	int	plus;
	int	space;
}	flag_t;

int	ft_printf(const char *str, ...);
int	ft_putchar(va_list data, __attribute__((unused)) flag_t *flag);
int	ft_putstr(va_list data, __attribute__((unused)) flag_t *flag);
int	ft_putadd(va_list data, flag_t *flag);
int	ft_putdigit(va_list data, flag_t *flag);
int	ft_putudigit(va_list data, __attribute__((unused)) flag_t *flag);
int	ft_puthex_lower(va_list data, flag_t *flag);
int	ft_puthex_upper(va_list data, flag_t *flag);
int	ft_putprecent(
		__attribute__((unused)) va_list data,
		__attribute__((unused)) flag_t *flag);

#endif
