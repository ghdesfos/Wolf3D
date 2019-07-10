# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/18 15:01:32 by ghdesfos          #+#    #+#              #
#    Updated: 2018/11/19 06:18:02 by ghdesfos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ = $(SRC:.c=.o)
SRC = main.c \
	  display_new_view.c \
	  find_obstacle_with_raycasting.c \
	  get_next_line.c \
	  initialize_map_and_player.c \
	  next_move.c \
	  useful_functions.c \
	  useful_functions_2.c
FLAGS =-Wall -Wextra -Werror
MLX_FOL =minilibx_macos/
NAME = wolf3d

all: $(NAME)

$(NAME):
	make -C $(MLX_FOL)
	gcc $(FLAGS) -o $(NAME) $(SRC) -L $(MLX_FOL) -lmlx -framework OpenGL -framework AppKit

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f *.gch

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
