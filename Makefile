# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:42:24 by rbaticle          #+#    #+#              #
#    Updated: 2025/05/15 11:46:08 by rbaticle         ###   ########.fr        #
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

INCLUDES = ./includes/
HEADER_FILES = miniRT.h
HEADERS = $(addprefix $(INCLUDES), $(HEADER_FILES))


all: $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -fr $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -fr $(NAME)
