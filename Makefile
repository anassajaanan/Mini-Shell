NAME		=	minishell

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g

ifeq ($(shell uname -p), i386)
	LIB_FLAGS	=	-L./lib/libft -lft -L/usr/local/Cellar/readline/8.1/lib -lreadline
	INCLUDES	=	-I./include -I./lib/libft -I/usr/local/Cellar/readline/8.1/include
else
	LIB_FLAGS	=	-L./lib/libft -lft -lreadline
	INCLUDES	=	-I./include -I./lib/libft
endif

SRCS		=	src/main.c \
				src/command.c \
\
				src/env/env_var.c \
				src/env/env_var_utils.c \
\
				src/parsing/free_parsing.c \
				src/parsing/null_terminate.c \
				src/parsing/parse_exec.c \
				src/parsing/parsing.c \
				src/parsing/token_helpers.c \
				src/parsing/validate_helpers.c \
				src/parsing/validate.c \
\
				src/execution/execution.c \
				src/execution/run_exec.c \
				src/execution/run_pipe.c \
				src/execution/run_redir.c \
				src/execution/run_redir_utils.c \
\
				src/builtins/cd.c \
				src/builtins/cd_utils.c \
				src/builtins/cd_helpers.c \
				src/builtins/echo.c \
				src/builtins/echo_utils.c \
				src/builtins/echo_helpers.c \
				src/builtins/env.c \
				src/builtins/exit.c \
				src/builtins/export.c \
				src/builtins/export_utils.c \
				src/builtins/pwd.c \
				src/builtins/unset.c \
\
				src/signals/signal.c \
\
				src/utils/queue.c \
				src/utils/utility.c \



OBJS		=	$(SRCS:.c=.o)

all			:	${NAME}


${NAME}		:	libft ${OBJS}
				$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIB_FLAGS) -o $(NAME)

libft		:
				@make -C ./lib/libft

%.o			:	%.c
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean		:
				@make clean -C ./lib/libft
				${RM} ${OBJS}

fclean		:	clean
				@make fclean -C ./lib/libft
				${RM} ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re


# **************************************************************************** #
# 									VALGRIND								   #

leaks_fd:
	make re && make clean && valgrind --track-fds=yes  ./minishell
# --suppressions=supress_readline \
# --log-file=valgrind-out.txt 
leaks:
	make re && make clean \
	&& valgrind --leak-check=full \
	--track-origins=yes \
	--show-leak-kinds=all --suppressions=.ignore_readline.txt --log-file=valgrind-out.txt \
	./minishell
# **************************************************************************** #