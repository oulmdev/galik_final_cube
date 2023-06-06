# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 01:44:53 by moulmoud          #+#    #+#              #
#    Updated: 2023/06/03 22:09:12 by moulmoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS =

OBJDIR = obj/
SRCDIR = src/

MLX = -lmlx -framework OpenGL -framework AppKit

SRC_FILES =  $(wildcard src/*.c)#ft_split.c libft_2.c libft.c main.c parsing.c gnl.c gnl_utils.c \
	print_message.c mapChecker.c mapNewLines.c textureChecker.c pars_ext.c \
	Update.c movement.c
SRC = $(notdir $(SRC_FILES))
OBJ = $(SRC:%.c=$(OBJDIR)%.o)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	$(CC) $(MLX) $(OBJ) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c src/cube3d.h
	$(CC)  -c $< -o $@

clean:
	rm -rf $(OBJDIR)
fclean: clean
	rm -f $(NAME)

re: fclean all
