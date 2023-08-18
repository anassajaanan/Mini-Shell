NAME			=	libft.a

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar -rcs

SRCS			=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
					ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
					ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
					ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
					ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strcmp.c ft_strncmp.c \
					ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
					ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
					ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

SRCS_LIBFT		=	$(addprefix ./libft/, $(SRCS))

SRCS_PRINTF		=	ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_puthex.c \
					ft_printf/ft_putnbr.c ft_printf/ft_putptr.c ft_printf/ft_putstr.c \
					ft_printf/ft_putunbr.c

SRCS_PRINTF_FD	=	ft_printf_fd/ft_printf_fd.c ft_printf_fd/putchar_fd.c ft_printf_fd/puthex_fd.c \
					ft_printf_fd/putnbr_fd.c ft_printf_fd/putptr_fd.c ft_printf_fd/putstr_fd.c \
					ft_printf_fd/putunbr_fd.c

SRCS_GNL		=	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c


OBJS_LIBFT		=	$(SRCS_LIBFT:.c=.o)
OBJS_PRINTF		=	$(SRCS_PRINTF:.c=.o)
OBJS_PRINTF_FD	=	$(SRCS_PRINTF_FD:.c=.o)
OBJS_GNL		=	$(SRCS_GNL:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_PRINTF_FD) $(OBJS_GNL)
					@echo "\n🔨 Building $(NAME)...\n"
					$(AR) $(NAME) $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_PRINTF_FD) $(OBJS_GNL)
					@echo "\n✅ $(NAME) created successfully!\n"

%.o				:	%.c
					$(CC) $(CFLAGS) -c $< -o $@

clean			:
					rm -f $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_PRINTF_FD) $(OBJS_GNL) 

fclean			:	clean
					rm -f $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re