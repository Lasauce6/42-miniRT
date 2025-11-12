# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jili <jili@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:42:24 by rbaticle          #+#    #+#              #
#    Updated: 2025/11/12 14:45:21 by jili             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS_DIR = ./srcs/
SRCS_NAMES = main.c \
			 parsing/parser.c \
			 parsing/parse_light.c \
			 parsing/parse_objs.c \
			 parsing/parse_utils.c \
			 parsing/parse_utils_2.c \
			 utils/color.c \
			 utils/numbers.c \
			 utils/obj_utils.c \
			 utils/ray_utils.c \
			 utils/vector.c \
			 utils/vector2.c \
			 utils/vector3.c \
			 utils/mlx_utils.c \
			 utils/exit.c \
			 utils/free.c \
			 rt/ray.c \
			 rt/hit.c \
			 rt/hit_cylinder.c \
			 rt/light.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_NAMES))

OBJ_DIR = ./objs/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS_NAMES:.c=.o))

LIBFT_DIR = ./libft/
LIBFT_LIB = ./libft/libft.a

MLX_DIR = ./mlx-linux/
MLX_LIB = ./mlx-linux/libmlx.a

INCLUDES = ./includes/
HEADER_FILES = miniRT.h
HEADERS = $(addprefix $(INCLUDES), $(HEADER_FILES))

MLX_FLAGS = -L$(MLX_DIR) -lmlx -Imlx_linux -L/usr/lib -lXext -lX11 -lm -lz
LFT_FLAGS = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) -I $(INCLUDES) $(OBJS) $(CFLAGS) $(MLX_FLAGS) $(LFT_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

fsan: $(LIBFT_LIB) $(MLX_LIB) $(HEADERS)
	$(CC) -I $(INCLUDES) $(SRCS) $(CFLAGS) $(MLX_FLAGS) $(LFT_FLAGS) -fsanitize=address -g3 -o $(NAME)

debug: $(LIBFT_LIB) $(MLX_LIB) $(HEADERS)
	$(CC) -I $(INCLUDES) $(SRCS) $(CFLAGS) $(MLX_FLAGS) $(LFT_FLAGS) -g3 -o $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) gnl

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -fr $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean
	rm -fr $(NAME)

re: fclean
	@make all --no-print-directory

.PHONY: all clean fclean re
