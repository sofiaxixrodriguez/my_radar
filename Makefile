##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC		=	./src/radar.c			\
			./src/parse.c		\
			./src/main.c		\
			./src/clock.c		\
			./src/sprites_hitboxes.c		\
			./src/collisions.c	\
			./src/lib.c		\

OBJ		=	$(SRC:.c=.o)

NAME	=	my_radar

CFLAGS	=	-W -Wall -lm -g -I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lm -lcsfml-window -lcsfml-system -lcsfml-graphics
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re:		fclean all
