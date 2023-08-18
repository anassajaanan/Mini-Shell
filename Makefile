NAME		=	minishell

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
LIB_FLAGS	=	-L./lib/libft -lft -L./lib/readline/lib -lreadline
INCLUDES	=	-I./include -I./lib/libft -I./lib/readline/include 

SRCS		=	src/main.c \
				src/echo.c \
				src/env.c \
				src/cd.c \
				src/unset.c \
				src/export.c \
				src/env_var.c \
				src/queue.c \
				src/utils.c \

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