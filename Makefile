NAME = philo

HEADER_SRC = philo.h
SRC = ./main.c \
      ./set_sim.c \
      ./parse.c \
      ./routine.c \
      ./actions.c \
      ./cutlery.c \
      ./threads.c \
      ./utils.c \
      ./clean.c \

OBJ = $(SRC:.c=.o)

CC = cc
CPPFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
