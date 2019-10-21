# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wta <wta@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 20:09:26 by wta               #+#    #+#              #
#    Updated: 2019/10/21 15:44:30 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
CC = gcc -O2

INC_DIR = includes
OBJ_DIR = objs
SRCS_DIR =	srcs
LIBFT = libft

HEADERS =		\
scop.h

SRCS =				\
main.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/, $(OBJ))
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $^ -L $(LIBFT) -lft -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(addprefix $(INC_DIR)/, $(HEADERS)) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(addprefix $(LIBFT)/, $(INC_DIR)) -c -o $@ $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -rf $(OBJ)
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all $(LIBFT) clean fclean re
