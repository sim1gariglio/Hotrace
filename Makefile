

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

test:
	make re
	rm -f file.txt
	@rm -f a.out
	gcc gen.c && ./a.out > file.txt && ./hotrace < file.txt

.PHONY: all clean fclean re