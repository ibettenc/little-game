# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+ +:+      +:+
#    By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 19:36:14 by ibettenc          #+#    #+#              #
#    Updated: 2026/08/06 18:25:32 by ibettenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################################################
## ARGUMENTS

NAME = cub3d

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Iincludes -Iincludes/mlx -Iincludes/GNL -Iincludes/libft -g

MLX_FLAGS = -L srcs/includes/mlx -lmlx -lXext -lX11 -lm

LIBFT = srcs/includes/libft/libft.a

MLX = srcs/includes/mlx/libmlx.a

###################################################
## SOURCES

SRC_DIR = srcs
OBJ_DIR = obj

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/utils/hooks.c \
      $(SRC_DIR)/utils/mlx_init.c \
      $(SRC_DIR)/utils/rgb_to_hex.c \
      $(SRC_DIR)/render/render.c \
      $(SRC_DIR)/render/player.c \
      $(SRC_DIR)/render/raycasting.c \
      $(SRC_DIR)/render/movement.c \
      $(SRC_DIR)/render/raycasting_utils.c \
      $(SRC_DIR)/parsing/file_errors.c \
      $(SRC_DIR)/parsing/floodfill.c \
      $(SRC_DIR)/parsing/free.c \
      $(SRC_DIR)/parsing/map_parsing.c \
      $(SRC_DIR)/parsing/map_functions.c \
      $(SRC_DIR)/parsing/parsing.c \
      $(SRC_DIR)/includes/GNL/get_next_line.c \
      $(SRC_DIR)/includes/GNL/get_next_line_utils.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

###################################################
## RULES

all: $(NAME)

$(LIBFT):
	@make -C srcs/includes/libft

$(MLX):
	@make -C srcs/includes/mlx

$(NAME): $(LIBFT) $(OBJ) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

##################################################
## CLEAN

clean:
	@rm -rf $(OBJ_DIR)
	@make -C srcs/includes/libft fclean
	@make -C srcs/includes/mlx clean

fclean: clean
	@rm -f $(NAME)
	@make -C srcs/includes/libft fclean
	@make -C srcs/includes/mlx clean

re: fclean all

.PHONY: all clean fclean re