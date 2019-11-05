# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wta <wta@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 20:09:26 by wta               #+#    #+#              #
#    Updated: 2019/11/06 16:49:35 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
CFLAGS = -Wall -Wextra -Werror# -g3 -fsanitize=address
CC = cc -O2

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	LGL := -lGL -lm
	LGL_INC := /usr/include/GLES3
else ifeq ($(UNAME_S), Darwin)
	LGL := -framework OpenGL -framework AppKit
	# LGL_INC := /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk/System/Library/Frameworks/OpenGL.framework/Headers
	LGL_INC := ~/.brew/include
	CFLAGS += -Wno-deprecated-declarations
endif

CURR_PATH = $(shell pwd)

INC_DIR = include
SRC_DIR = src

LIB_DIR = lib

LFT_DIR = $(LIB_DIR)/libft
LFT = $(LFT_DIR)/libft.a
LFT_INC = $(LFT_DIR)/$(INC_DIR)

OBJ_DIR = obj
_OBJ_DIR =						\
	$(OBJ_DIR)					\
	$(OBJ_DIR)/entities			\
	$(OBJ_DIR)/entities/shader	\
	$(OBJ_DIR)/error			\
	$(OBJ_DIR)/sdl				\
	$(OBJ_DIR)/tga_loader

DEPS_DIR = $(LIB_DIR)/dep
BUILD_DIR = $(LIB_DIR)/build

DEPS_PATH = $(addprefix $(CURR_PATH)/, $(DEPS_DIR))
BUILD_PATH = $(addprefix $(CURR_PATH)/, $(BUILD_DIR))

SDL2 = SDL2
LSDL2 = $(DEPS_DIR)/lib/libSDL2.a
LSDL2_INC = $(BUILD_DIR)/$(INC_DIR)/$(SDL2)

LSDL2_DIR = 		\
	$(DEPS_DIR)		\
	$(BUILD_DIR)

DIRS =				\
	$(_OBJ_DIR)		\
	$(LSDL2_DIR)

SDL_OPTION =							\
	-q																	\
	--prefix=$(DEPS_PATH)								\
	--exec-prefix=$(DEPS_PATH)					\
	--bindir=$(BUILD_PATH)/bin					\
	--includedir=$(BUILD_PATH)/include	\
	--datarootdir=$(BUILD_PATH)/data

HEADERS =			\
error.h				\
scop.h

SRC =							\
entities/shader/core.c			\
entities/shader/setters.c		\
entities/shader/shader.c		\
error/error.c								\
sdl/event.c									\
sdl/init.c									\
sdl/quit.c									\
tga_loader/data.c						\
tga_loader/getters.c				\
tga_loader/tga_loader.c			\
main.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(LSDL2): | $(LSDL2_DIR)
	mkdir -p $(BUILD_DIR)/sdl2
	cd $(BUILD_DIR)/sdl2				&&\
	../../sdl2/configure $(SDL_OPTION)	&&\
	make -j10							&&\
	make install

$(LFT):
	$(MAKE) -j10 -C $(LFT_DIR)

$(NAME): $(LFT) $(LSDL2) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LGL) -L $(LFT_DIR) -lft -L $(DEPS_DIR)/lib -l$(SDL2) -o $@

$(OBJ_DIR)/%.o: $(addprefix $(SRC_DIR)/, %.c) $(addprefix $(INC_DIR)/, $(HEADERS)) | $(_OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LGL_INC) -I $(INC_DIR) -I $(LFT_INC) -I $(LSDL2_INC) -c -o $@ $<

$(DIRS):
	mkdir -p $@

tga_test:
	gcc -I include -I lib/libft/include src/tga_loader/*.c test/test_tga.c -o test_tga -L lib/libft -lft
	./test_tga

info:
	@echo "OBJ_DIR: $(OBJ_DIR)"
	@echo "SRC_DIR: $(SRC_DIR)"
	@echo "SRC: $(SRC)"

clean:
	$(MAKE) -C $(LFT_DIR) clean
	/bin/rm -rf $(_OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LFT_DIR) fclean
	/bin/rm -f $(NAME)
	/bin/rm -rf $(DIRS)

re: fclean all

.PHONY: all clean fclean re
