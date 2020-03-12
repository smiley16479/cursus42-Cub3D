# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 23:20:17 by adtheus           #+#    #+#              #
#    Updated: 2020/03/10 15:29:50 by adtheus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# LIB_DIR = $(shell find lib -type d -maxdepth 1 | grep 'lib/')
# INC_DIR = $(shell find includes -type d) $(foreach dir, $(LIB_DIR), $(shell find -f $(dir)/includes -type d))

LIB_DIR =  lib/minilibx_opengl_20191021
OBJ_DIR = obj

SRC = 	main.c 					angle_convert.c 			at_app_initializer.c \
		at_image.c 				at_mlx_hook.c 				at_mlx_measure.c \
		at_mlx_pixel_put.c		at_mlx_player_handler.c		at_mlx_render.c \
		at_mlx_shape_circle.c	at_mlx_shape_square.c		at_vector2.c \
		at_mlx_color_handler.c	at_mlx_sprite.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
LIB = mlx
FRAMEWORK = AppKit OpenGL

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

CFLAG = -fsanitize=address -g3
# flag : -o3 pour accelerer l'execution du code
IFLAG = $(foreach dir, $(INC_DIR), -I $(dir) )
LFLAG = $(foreach lib, $(LIB), -l $(lib) ) $(foreach dir, $(LIB_DIR), -L $(dir) )
#LFLAG = -L lib/libft -L lib/mlx -l mlx -l libft

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LFLAG = -L/lib/x86_64-linux-gnu/ -lXext -lX11 -lmlx -lbsd -lm
else
	LFLAG += $(foreach framework, $(FRAMEWORK), -framework $(framework) )
endif

all		: $(NAME)

show	:
	@echo "SRC_DIR : $(SRC_DIR)\n"
	@echo "LIB_DIR : $(LIB_DIR)\n"
	@echo "INC_DIR : $(INC_DIR)\n"
	@echo "CFLAG : $(CFLAG)\n"
	@echo "IFLAG : $(IFLAG)\n"
	@echo "LFLAG : $(LFLAG)\n"
	@echo "SRC :$(foreach file, $(SRC),\n\t$(file))\n"
	@echo "OBJ :$(foreach file, $(OBJ),\n\t$(file))\n"

#@echo "LIB :$(foreach lib, $(LIB),\n\t$(lib))\n"
#LIB = ft mlx
#LFLAGS = 	$(foreach dir, $(LIB_DIR), -L $(dir) ) $(foreach lib, $(LIB), -l$(lib) ) -framework OpenGL -framework AppKit

## -c = definit les fichiers sources a compiler
## -o = change le nom du fichier d'output
## $@ = la cible de la regle
## $< = la premiere dependance de la regle
## $^ = les dependances de la regle
$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(CFLAG) $(IFLAG) -c $< -o $@

$(NAME)	: $(OBJ)
	@gcc $(OBJ) $(CFLAG) $(IFLAG) $(LFLAG) -o $@

debug : $(NAME)
	@./$(NAME)

install :
#	make -C lib/libft
	make -C lib/mlx

re-install :
#	make -C lib/libft re
	make -C lib/mlx re

clean	:
	@rm -f $(OBJ)

fclean	: clean
	@rm -f $(NAME)

re		: fclean all
