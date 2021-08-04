NAME	= philo
SRCS	= ./srcs/philosophers.c \
		  ./srcs/actions/actions.c \
		  ./srcs/forks/forks.c \
		  ./srcs/print/print.c \
		  ./srcs/time/time.c \
		  ./srcs/util/util.c
HEADERS	= ./includes/philosophers.h
OBJS	= $(SRCS:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all
