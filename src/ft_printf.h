/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 21:30:50 by eestelle          #+#    #+#             */
/*   Updated: 2022/01/10 16:47:01 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_flag
{
	int		sharp;
	int		flag_w;
	int		flag_p;
	int		widht;
	int		precision;
	char	plus_space;
	char	minus_zero;
}	t_flag;

int		ft_printf(const char *str, ...);
int		ft_putchar(va_list data, t_flag *flag);
int		ft_putstr(va_list data, t_flag *flag);
int		ft_putadd(va_list data, t_flag *flag);
int		ft_putdigit(va_list data, t_flag *flag);
int		ft_putudigit(va_list data, t_flag *flag);
int		ft_puthex_lower(va_list data, t_flag *flag);
int		ft_puthex_upper(va_list data, t_flag *flag);
int		ft_putprecent(
			__attribute__((unused)) va_list data,
			__attribute__((unused)) t_flag *flag);
void	ft_check_t_flag(t_flag *flag, va_list data, const char *c, int *i);
void	ft_check_flag( char *str, int *i, t_flag *flag);
void	ft_flag_init(t_flag *flag);
int		ft_isnum(char c);
int		ft_check_char(char c);
int		ft_atoi(const char *c, int *i, int flag);
int		ft_strlen(char *str);
int		ft_max(int a, int b, int c);

#endif
