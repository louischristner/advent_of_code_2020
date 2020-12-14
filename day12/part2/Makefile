CC		=	g++

SRC		=	main.cpp	\
			Ship.cpp	\
			Waypoint.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	exec

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
