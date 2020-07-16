# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 23:20:17 by adtheus           #+#    #+#              #
#    Updated: 2020/07/15 16:17:57 by adtheus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
MAP_TEST = map/map1.cub

# LIB_DIR = $(shell find lib -type d -maxdepth 1 | grep 'lib/')
# INC_DIR = $(shell find includes -type d) $(foreach dir, $(LIB_DIR), $(shell find -f $(dir)/includes -type d))

LIB_DIR =  lib/minilibx_opengl_20191021
SRC_DIR = src
OBJ_DIR = obj
SRC_BONUS_DIR = src_bonus
OBJ_BONUS_DIR = obj_bonus

SRC = 			main.c 							angle_convert.c 				at_app_initializer.c \
				at_image.c 						at_mlx_hook.c 					at_mlx_measure.c \
				at_mlx_pixel_put.c				at_mlx_player_handler.c			at_mlx_render.c \
				cub3d_map_analyser_tools_1.c	cub3d_map_analyser_tools_2.c	cub3d_map_analyser_tools_3.c\
				at_mlx_sprite.c					at_vector2.c					cub3d_map_analyser.c\
				error_handling.c				ft_split.c						gnl.c\
				gnl_2000.c						at_bmp.c						cub3d_map_info_init.c\
				at_terminal_display.c

SRC_BONUS = 	main.c 							angle_convert.c 					at_app_initializer.c \
				at_image.c 						at_mlx_hook.c 						at_mlx_measure.c \
				at_mlx_pixel_put.c				at_mlx_player_handler.c				at_mlx_render.c \
				cub3d_map_analyser_tools_1.c	cub3d_map_analyser_tools_2.c		cub3d_map_analyser_tools_3.c\
				at_mlx_sprite.c					at_vector2.c						cub3d_map_analyser.c\
				error_handling.c				ft_split.c							gnl.c\
				gnl_2000.c						at_bmp.c							cub3d_map_info_init.c\
				at_terminal_display.c	at_mlx_shape_square.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR)/, $(SRC_BONUS:%.c=%.o))
LIB = mlx
FRAMEWORK = AppKit OpenGL

#vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

CFLAG = -fsanitize=address -g3 -Wall -Wextra -Werror
# flag : -o3 pour accelerer l'execution du code
IFLAG = $(foreach dir, $(INC_DIR), -I $(dir) ) -I ./lib/minilibx_opengl_20191021
LFLAG = $(foreach lib, $(LIB), -l $(lib) ) $(foreach dir, $(LIB_DIR), -L $(dir) )
#LFLAG = -L lib/libft -L lib/mlx -l mlx -l libft

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LFLAG = -L./lib/linux_lib -lmlx -lXext -lX11 -lbsd -lm
	CFLAG += -DLINUX=1
else
	LFLAG += $(foreach framework, $(FRAMEWORK), -framework $(framework) )
	CFLAG += -DLINUX=0
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
	@echo "SRC_BONUS :$(foreach file, $(SRC_BONUS),\n\t$(file))\n"
	@echo "OBJ :$(foreach file, $(OBJ),\n\t$(file))\n"
	@echo "OBJ_BONUS :$(foreach file, $(OBJ_BONUS),\n\t$(file))\n"

#@echo "LIB :$(foreach lib, $(LIB),\n\t$(lib))\n"
#LIB = ft mlx
#LFLAGS = 	$(foreach dir, $(LIB_DIR), -L $(dir) ) $(foreach lib, $(LIB), -l$(lib) ) -framework OpenGL -framework AppKit

## -c = definit les fichiers sources a compiler
## -o = change le nom du fichier d'output
## $@ = la cible de la regle
## $< = la premiere dependance de la regle
## $^ = les dependances de la regle
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(CFLAG) $(IFLAG) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o : $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(OBJ_BONUS_DIR)  
	@gcc $(CFLAG) $(IFLAG) -c $< -o $@

$(NAME)	: $(OBJ)
	@gcc $(OBJ) $(CFLAG) $(IFLAG) $(LFLAG) -o $@

bonus : $(OBJ_BONUS)
	@gcc $(OBJ_BONUS) $(CFLAG) $(IFLAG) $(LFLAG) -o $@

debug : $(NAME)
	@./$(NAME) $(MAP_TEST)

install :
#	make -C lib/libft
	make -C lib/mlx

re-install :
#	make -C lib/libft re
	make -C lib/mlx re

clean	:
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean	: clean
	@rm -f $(NAME)
	@rm -f bonus

re		: fclean all
