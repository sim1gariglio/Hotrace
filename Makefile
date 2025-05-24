

CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

NAME = hotrace

SRCS = main.c readline.c \
	   parseInput.c hashMap.c ft_strcmp.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re