

CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

NAME = hotrace

SRCS = main.c utils.c get_next_line.c \
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

profile: CFLAGS += -pg -O0 -fno-inline -fno-builtin
profile: re

testGen:
	cc gen.c -o testGen
	./testGen > input.hrt

report: profile testGen
	@./$(NAME) < input.hrt
	gprof -lb $(NAME) > profile.txt

.PHONY: all clean fclean re