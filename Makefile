# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/30 15:30:51 by pivanovi          #+#    #+#              #
#    Updated: 2016/01/13 14:47:44 by pivanovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = fractol

SRC =	src/main.c				\
		src/draw.c				\
		src/list.c				\
		src/loop.c				\
		src/loop2.c				\
		src/utils.c				\
		src/julia.c				\
		src/threads.c			\
		src/mandelbrot.c		\
		src/buddhabrot.c		\
		src/args_management.c

OBJ = $(SRC:.c=.o)

CFLAGS += -I./includes -I./libft
LIBX = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $@ $(LIBX)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

