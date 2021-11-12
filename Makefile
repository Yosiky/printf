CC = gcc
CFLAGS	= -Wall -Wextra -Werror -g

SRC	=	\
		ft_printf

OBJ	=	$(SRC:=.o)
NAME	= libftprintf.a

.PHONY:	all clean fclean re
all:	$(NAME)

$(NAME):	$(OBJ)
	ar cr $(NAME) $(OBJ)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:		\
		fclean	\
		all
