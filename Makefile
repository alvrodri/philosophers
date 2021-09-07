NAME	= philo
SRCS	= ./srcs/philosophers.c \
		  ./srcs/actions/actions.c \
		  ./srcs/forks/forks.c \
		  ./srcs/print/print.c \
		  ./srcs/time/time.c \
		  ./srcs/util/util.c \
		  ./srcs/philosopher/philosopher.c
HEADERS	= ./includes/philosophers.h
OBJS	= $(SRCS:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) -I $(HEADERS) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re