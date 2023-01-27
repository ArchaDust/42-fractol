# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberneli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/16 14:59:12 by aberneli          #+#    #+#              #
#    Updated: 2021/11/24 14:16:15 by aberneli         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := fractol

CC := gcc
FLAGS := -Wall -Wextra -Werror -Ofast -I. -Iminilibx

HEADER := fractol.h mlx_input.h

SRC := main.c init.c draw.c image.c color.c mandel.c helper.c hook.c move.c \
	julia.c input.c custom.c ft_putstr_fd.c ft_strncmp.c ft_atoi.c \
	ft_memset.c ft_strlen.c
OBJ := $(SRC:.c=.o)

LIBS = libmlx.dylib
LIBS_CHECK = minilibx/libmlx.dylib
LIB_FLAGS := -Lminilibx -lmlx -lpthread -D_REENTRANT -framework OpenGL \
	-framework AppKit

MAKEFILEV = Makefile

all: $(NAME)

$(NAME): $(LIBS) $(OBJ) $(MAKEFILEV)
	$(CC) $(FLAGS) $(LIB_FLAGS) $(OBJ) -o $(NAME) $(LIBS)

%.o: %.c $(HEADER) $(MAKEFILEV)
	$(CC) $(FLAGS) -Iminilibx -c $< -o $@

$(LIBS): $(LIBS_CHECK)
	cp minilibx/libmlx.dylib .

$(LIBS_CHECK):
	make -C minilibx

clean:
	rm -f $(OBJ)

fclean: clean libclean
	rm -f $(NAME)

libclean:
	make -C minilibx clean
	rm $(LIBS)

re: fclean all

normy:
	norminette $(SRC) $(HEADER)

.PHONY: all clean fclean re libclean normy
