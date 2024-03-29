# author: BEAUFILS Noah
# date: march/27/2024

SRC =	algorithm/random.c		\
		algorithm/md5.c			\
		main.c

INCLUDE = -I ./header

OBJ = $(SRC:.c=.o)
CC = cc
RM = rm -f
DEBUG = 
DEFINE = -DTEST
FLAGS = -Wall -Wextra -Werror $(DEBUG)

NAME = duck

%.o : %.c
	$(CC) $(DEFINE) $(FLAGS) $(INCLUDE) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDE) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: test all clean fclean re

.SILENT: