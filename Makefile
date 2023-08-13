NAME = minishell

SRCS = ./src/main.c \
		./src/echo.c \
		./lib/get_next_line/get_next_line.c \
		./lib/get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

INCLUDE = ./include

CFLAGS = -Wall -Wextra -Werror -g


${NAME}: ${OBJS}
	@make -C ./lib/libft
	@make -C ./lib/ft_printf
	# ${CC} ${CFLAGS} -L./lib/libft -lft -L./lib/ft_printf -lftprintf -o ${NAME} ${OBJS}
	${CC} ${CFLAGS} -I ${INCLUDE} -L./lib/libft -lft -L./lib/ft_printf -lftprintf -o ${NAME} ${OBJS}

all: ${NAME}

clean:
	@make clean -C ./lib/libft
	@make clean -C ./lib/ft_printf
	rm -f ${OBJS}

fclean: clean
	@make fclean -C ./lib/libft
	@make fclean -C ./lib/ft_printf
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re