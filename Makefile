.PHONY: all clean fclean re bonus libft mlx create_dir
.SILENT: mlx

NAME = cub3D
LIBFT_NAME = libft.a

OFLAGS	  	 = -O
OS			 = $(shell uname)

############################# MLX ############################

ifeq ($(OS), Linux)
	OS_FLAG		= -D LINUX
	MLX_DIR		= minilibx/mlx_opengl
	MLX_NAME	= libmlx.a
	MLX_FLAGS	= -L. -lmlx -lXext -lX11 -lm
else
	MLX_DIR		= minilibx/mlx_mac
	MLX_NAME	= libmlx.a
	MLX_FLAGS	= -L. -lmlx -framework OpenGL -framework AppKit
endif

######################### CC && FLAGS ########################

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_FLAGS		= -L $(LFT_DIR) -lft
INCLUDE_FLAGS 	= -I $(INC_DIR) -I $(LFT_DIR) -I $(GNL_DIR) -I $(MLX_DIR)

######################### DIRECTORIES ########################

SRC_DIR = src
BNS_DIR = bonus
OBJ_DIR = obj
LFT_DIR = libft
INC_DIR = include
GNL_DIR = get_next_line

######################### SOURCES ############################

SOURCES =	main.c \
			check_arguments.c \
			errors.c \
			arrays.c \
			map_utils.c \
			vector.c \
			map_validation.c \
			raycasting.c \
			key_action.c \
			init.c \
			init_ext.c \
			colors.c \
			math_utils.c \
			music.c \
			save.c \
			free_all.c \
			sprites.c \
			parse_map.c \
			parse_num.c \
			parse_prm.c \
			parse_skip.c \
			parse_print.c\
			parse_check.c \
			parse_identify.c \
			parse_scene_file.c \
			parse_is_complete.c \
			engine.c \
			engine_move.c \
			engine_calculate.c \
			engine_mouse.c \
			engine_utils.c \
			engine_calculate_ext.c \
			engine_draw_bonus.c \
			engine_draw_ext.c \
			engine_draw_sprites.c \
			engine_draw.c \
			engine_put_image.c \
			engine_textures.c\
			engine_init_bonus_flags.c

ifeq ($(BSRC), "TRUE")
	B_SOURCES = 
else
	B_SOURCES = 
endif



GNL_SRC = 	get_next_line.c

######################## OBJECT FILES ########################

GNL_OBJ = $(addprefix $(OBJ_DIR)/, $(GNL_SRC:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

######################## HEADERS #############################

HEADERS = $(INC_DIR)/*.h

######################## INSTRUCTIONS ########################

all: libft mlx create_dir $(ACT_DIR) $(NAME)

r: all
	./${NAME} ${MAP}

s: all
	./${NAME} ${MAP} --save

br: bonus
	./${NAME} ${MAP}

bs: bonus
	./${NAME} ${MAP} --save

bdebug:
	$(MAKE) DEBUG="-g" bonus MAP=${MAP}

debug:
	$(MAKE) DEBUG="-g" MAP=${MAP}

create_dir:
	@mkdir -p $(OBJ_DIR)

$(GNL_OBJ): $(GNL_DIR)/$(GNL_SRC)
	@$(CC) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

libft:
	@$(MAKE) bonus -C $(LFT_DIR) --no-print-directory

mlx:
	@$(MAKE) -C $(MLX_DIR) -s --no-print-directory 
	@cp $(MLX_DIR)/$(MLX_NAME) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LFT_DIR)/$(LIBFT_NAME) $(MLX_DIR)/$(MLX_NAME) $(GNL_OBJ)
	@$(CC) $(DEBUG) $(BONUS) $(OS_FLAG) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

$(NAME): $(OBJECTS) $(GNL_OBJ) $(HEADERS) 
	@$(CC) $(DEBUG) $(BONUS) $(CFLAGS) $(GNL_OBJ) $(OBJECTS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $@ -lpthread
	@echo "$(NAME) created"

clean:
	@$(MAKE) clean -C $(LFT_DIR) --no-print-directory 
	@$(MAKE) clean -C $(MLX_DIR) --no-print-directory 
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LFT_DIR) --no-print-directory
	@rm -rf *.bmp
	@rm -rf ${MLX_NAME}
	@rm -rf ${NAME}
	@echo "${NAME} has been deleted"

bonus:
	@$(MAKE) BONUS="-D BONUS" BSRC="TRUE" all --no-print-directory

re: fclean all