# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:42:24 by rbaticle          #+#    #+#              #
#    Updated: 2025/05/15 15:30:32 by rbaticle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS_DIR = ./srcs/
SRCS_NAMES = main.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_NAMES))

OBJ_DIR = ./objs/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS_NAMES:.c=.o))

LIBFT_DIR = ./libft/
LIBFT_LIB = ./libft/libft.a

MLX_DIR = ./minilibx-linux/
MLX_LIB = ./minilibx-linux/libmlx.a

INCLUDES = ./includes/
HEADER_FILES = miniRT.h
HEADERS = $(addprefix $(INCLUDES), $(HEADER_FILES))

CFLAGS_MAIN = -L$(MLX_DIR) -lX11 -lXext -lmlx -lm
CFLAGS_MAIN += -L$(LIBFT_DIR) -lft
# CFLAGS += -lm

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDES) $(OBJS) $(CFLAGS_MAIN) -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

fsan: $(LIBFT_LIB) $(MLX_LIB) $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDES) $(SRCS) $(CFLAGS_MAIN) -fsanitize=address -g3 -o $(NAME)

debug: $(LIBFT_LIB) $(MLX_LIB) $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDES) $(SRCS) $(CFLAGS_MAIN) -g3 -o $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -fr $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re
