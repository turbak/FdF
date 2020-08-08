NAME = fdf
PATH_SRC = ./
PATH_OBJ = ./
PATH_INC = ./libft/includes/

CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADER = fdf.h

all:
	gcc *.c libft/libft.a -lmlx -framework OpenGL -framework AppKit
