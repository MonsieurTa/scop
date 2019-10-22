# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: william <william@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 20:09:26 by wta               #+#    #+#              #
#    Updated: 2019/10/22 14:20:20 by william          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
CC = cc -O2

CURR_PATH = $(shell pwd)

INC_DIR = include
SRCS_DIR =	src

LFT_DIR = libft
LFT = $(LFT_DIR)/libft.a

OBJ_DIR = obj
DEPS_DIR = dep
BUILD_DIR = build

DEPS_PATH = $(addprefix $(CURR_PATH)/, $(DEPS_DIR))
BUILD_PATH = $(addprefix $(CURR_PATH)/, $(BUILD_DIR))

SDL2 = SDL2
LSDL2 = $(DEPS_DIR)/lib/libSDL2.a

LSDL2_DIR = 		\
	$(DEPS_DIR)		\
	$(BUILD_DIR)

DIRS =				\
	$(OBJ_DIR)		\
	$(LSDL2_DIR)

SDL_OPTION =							\
	-q									\
	--prefix=$(DEPS_PATH)				\
	--exec-prefix=$(DEPS_PATH)			\
	--bindir=$(BUILD_PATH)/bin			\
	--includedir=$(BUILD_PATH)/include	\
	--datarootdir=$(BUILD_PATH)/data

HEADERS =			\
scop.h

SRCS =				\
main.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(LSDL2): | $(LSDL2_DIR)
	mkdir -p $(BUILD_DIR)/sdl2
	cd $(BUILD_DIR)/sdl2				&&\
	../../sdl2/configure $(SDL_OPTION)	&&\
	make -j10							&&\
	make install

$(LFT):
	$(MAKE) -j10 -C libft

$(NAME): $(LFT) $(LSDL2) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L $(LFT_DIR) -lft -L $(DEPS_DIR)/lib -l$(SDL2) -o $@

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(INC_DIR)/$(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LFT_DIR)/$(INC_DIR) -I $(BUILD_DIR)/$(INC_DIR)/$(SDL2) -c -o $@ $<

$(DIRS):
	mkdir -p $@

clean:
	$(MAKE) -C libft clean
	/bin/rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)
	/bin/rm -f $(DIRS)

re: fclean all

.PHONY: all clean fclean re
