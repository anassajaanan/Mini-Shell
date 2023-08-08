NAME = minishell

SRCS = ./src/main.c \
		./src/echo.c \
		./src/export.c \
		./src/env_var.c \
		./src/utils.c \
		./src/split.c \
		./src/cmd.c \
		./src/queue.c \
		./src/cmd_parser.c \
		./lib/get_next_line/get_next_line.c \
		./lib/get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror 

READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib
	
INCLUDE = -Iinclude -I$(READLINE_DIR)/include 

${NAME}: ${OBJS}
	@make -C ./lib/libft
	@make -C ./lib/ft_printf
	${CC} ${CFLAGS} ${INCLUDE} -L./lib/libft -lft -L./lib/ft_printf -lftprintf -o ${NAME} ${OBJS}

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