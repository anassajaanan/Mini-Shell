NAME = minishell

SRCS = ./src/main.c \
		./src/echo.c \
		./lib/get_next_line/get_next_line.c \
		./lib/get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

${NAME}: ${OBJS}
	@make -C ./lib/libft
	${CC} ${CFLAGS} -L./lib/libft -lft -o ${NAME} ${OBJS}

all: ${NAME}

clean:
	@make clean -C ./lib/libft
	rm -f ${OBJS}

fclean: clean
	@make fclean -C ./lib/libft
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re