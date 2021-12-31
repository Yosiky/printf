#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_putchar(va_list data);
int	ft_putstr(va_list data);
int	ft_putadd(va_list data);
int	ft_putdigit(va_list data);
int	ft_putudigit(va_list data);
int	ft_puthex_lower(va_list data);
int	ft_puthex_upper(va_list data);
int	ft_putprecent(va_list data);
int	ft_strlen(char *str);

#endif