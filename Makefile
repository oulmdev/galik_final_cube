# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 01:44:53 by moulmoud          #+#    #+#              #
#    Updated: 2023/06/13 13:07:55 by moulmoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = #-Wall -Wextra -Werror #-fsanitize=address

OBJDIR = obj/
SRCDIR = src/

MLX = -lmlx -framework OpenGL -framework AppKit 

SRC_FILES =  $(wildcard src/*.c)
SRC = $(notdir $(SRC_FILES))
OBJ = $(SRC:%.c=$(OBJDIR)%.o)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MLX) $(OBJ) -o $(NAME)
	# @clear
$(OBJDIR)%.o: $(SRCDIR)%.c src/cube3d.h
	$(CC) $(CFLAGS) -c $< -o $@
	# @clear

clean:
	rm -rf $(OBJDIR)
fclean: clean
	rm -f $(NAME)

re: fclean all
