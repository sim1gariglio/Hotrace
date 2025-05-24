

CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

NAME = hotrace

SRCS = main.c ft_strcmp.c\
	   parseInput.c hashMap.c handle_capacity.c read_line.c\

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
	rm -f $(NAME) input.hrt testGen
	

.PHONY: all clean fclean re