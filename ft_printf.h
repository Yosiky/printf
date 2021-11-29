#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_flag
{
	int	len;
	int	min_len;
	char	begin;
	char	sharp;
	char	sign;
}	t_flag;

int			ft_printf(const char *str, ...);
size_t	ft_get_flag(const char *str, t_flag *flag);
size_t	ft_char_d(t_flag *flag, int value);
size_t	ft_char_u(t_flag *flag, unsigned int value);
size_t	ft_char_p(t_flag *flag, void *value);
size_t	ft_char_c(t_flag *flag, char value);
size_t	ft_char_s(t_flag *flag, char *value);
size_t	ft_char_x(t_flag *flag, int value);
size_t	ft_char_X(t_flag *flag, int value);

#endif
