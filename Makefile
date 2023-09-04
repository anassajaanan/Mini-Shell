NAME		=	minishell

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g

# ifeq ($(shell uname -p), i386)
# 	LIB_FLAGS	=	-L./lib/libft -lft -L/usr/local/Cellar/readline/8.1/lib -lreadline
# 	INCLUDES	=	-I./include -I./lib/libft -I/usr/local/Cellar/readline/8.1/include
# else
# 	LIB_FLAGS	=	-L./lib/libft -lft -lreadline
# 	INCLUDES	=	-I./include -I./lib/libft
# endif

LIB_FLAGS	=	-L./lib/libft -lft -L./lib/readline/lib -lreadline
INCLUDES	=	-I./include -I./lib/libft -I./lib/readline/include

SRCS		=	src/main.c \
				src/command.c \
				src/helpers.c \
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
				src/parsing/process_args.c \
				src/parsing/process_args_utils.c \
				src/parsing/process_args_helpers.c \
\
				src/execution/run_cmd.c \
				src/execution/run_exec.c \
				src/execution/run_exec_utils.c \
				src/execution/run_pipe.c \
				src/execution/run_redir.c \
\
				src/builtins/cd.c \
				src/builtins/echo.c \
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
				src/utils/free.c \



OBJS		=	$(SRCS:.c=.o)

all			:	${NAME}

${NAME}		:	${OBJS}
				@make -C ./lib/libft
				$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIB_FLAGS) -o $(NAME)



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