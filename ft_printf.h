#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_flag
{
	size_t	len;
	size_t	min_len;
	char	begin;
	char	sharp;
	char	sign;
}	t_flag;

int	ft_printf(const char *str, ...);

#endif
