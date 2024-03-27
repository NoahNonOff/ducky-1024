# author: BEAUFILS Noah
# date: march/26/2024

SRC =	algorithm/random.c		\
		algorithm/md5.c			\
		main.c

INCLUDE = -I ./header

OBJ = $(SRC:.c=.o)
CC = cc
RM = rm -f
DEBUG = 
FLAGS = -Wall -Wextra -Werror $(DEBUG)

NAME = duck

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDE) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re

.SILENT: