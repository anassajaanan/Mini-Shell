NAME =	libftprintf.a

SRC =	ft_printf.c ft_putchar.c ft_puthex.c ft_putnbr.c ft_putptr.c ft_putstr.c ft_putunbr.c

OBJ = ${SRC:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -fr

${NAME}	:	${OBJ}
			ar -rcs ${NAME} ${OBJ}

all		:	${NAME}

clean	:
			${RM} ${OBJ}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re