CC 		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

OBJ_DIR	=	obj
SRC_DIR	=	src

SRC		=	main			\
			ft_putsymbol	\
			ft_putdigit		\
			ft_puthex		\
			ft_putadd		\
			ft_flags		\
			ft_other

OBJ		=	${addprefix $(OBJ_DIR)/,$(SRC:=.o)}
HEADER	=	src/ft_printf.h

NAME	=	libftprintf.a

all:		$(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

$(NAME):	$(HEADER) $(OBJ) 
	ar cr $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

bonus: all
