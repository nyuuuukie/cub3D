.PHONY: all clean fclean re bonus libft libbass mlx create_dir
.SILENT: mlx

NAME = cub3D
LIBFT_NAME = libft.a

OFLAGS	  	 = -O
OS			 = $(shell uname)
ARCH		 = $(shell uname -m)

############################# MLX ############################

ifeq ($(OS), Linux)
	OS_FLAG		= -D LINUX
	MLX_DIR		= minilibx/mlx_opengl
	MLX_NAME	= libmlx.a
	MLX_FLAGS	= -L ${MLX_DIR} -lmlx -lXext -lX11 -lm
else
	MLX_DIR		= minilibx/mlx_mac
	MLX_NAME	= libmlx.a
	MLX_FLAGS	= -L ${MLX_DIR} -lmlx -framework OpenGL -framework AppKit
endif

######################### CC && FLAGS ########################

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_FLAGS		= -L $(LFT_DIR) -lft
LIBBASS_FLAGS   = -L ./libbass -lbass
LIBBASS_EXTRA   = install_name_tool -change @loader_path/libbass.dylib @loader_path/libbass/libbass.dylib $(NAME) 
INCLUDE_FLAGS 	= -I $(INC_DIR) -I $(LFT_DIR) -I $(GNL_DIR) -I $(MLX_DIR) -I $(LIBBASS_DIR)

######################### DIRECTORIES ########################

SRC_DIR = src
BNS_DIR = bonus
OBJ_DIR = obj
LFT_DIR = libft
INC_DIR = include
GNL_DIR = get_next_line
LIBBASS_DIR = libbass

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
			engine_init_bonus_flags.c\
			engine_get_color.c\
			engine_check_pos.c\
			engine_defined_functions.c\
			engine_defined_functions_ext.c\
			engine_init.c\
			engine_next.c

HEADER_FILES = cub3d.h \
				error.h \
				events.h \
				keycodes.h \
				settings.h \
				structures.h \
				bool.h \
				music.h

ifeq ($(BSRC), "TRUE")
	B_LIB = $(LIBBASS_FLAGS) $(LIBBASS_EXTRA)
else
	B_LIB = 
endif


GNL_SRC = 	get_next_line.c

######################## OBJECT FILES ########################

GNL_OBJ = $(addprefix $(OBJ_DIR)/, $(GNL_SRC:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))


######################## HEADERS #############################

HEADERS = $(addprefix $(INC_DIR)/, $(HEADER_FILES))

######################## INSTRUCTIONS ########################

all: libbass libft mlx create_dir $(GNL_OBJ) $(NAME)

create_dir:
	@mkdir -p $(OBJ_DIR)

$(GNL_OBJ): $(GNL_DIR)/$(GNL_SRC)
	@$(CC) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

libft:
	@$(MAKE) -C $(LFT_DIR) bonus

mlx:
	@$(MAKE) -C $(MLX_DIR)

libbass:
	@$(MAKE) -C $(LIBBASS_DIR) ${ARCH}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MLX_DIR)/$(MLX_NAME) $(GNL_OBJ)
	@$(CC) $(DEBUG) $(BONUS) $(OS_FLAG) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

$(NAME): $(OBJECTS) $(GNL_OBJ) $(HEADERS) 
	$(CC) $(DEBUG) $(BONUS) $(CFLAGS) $(GNL_OBJ) $(OBJECTS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $@ $(LIBBASS_FLAGS)
	${LIBBASS_EXTRA}
	@echo "$(NAME) created"

clean:
	@$(MAKE) clean -C $(LFT_DIR) --no-print-directory 
	@$(MAKE) clean -C $(MLX_DIR) --no-print-directory 
	@rm -rf $(OBJ_DIR)/*.o

fclean: clean
	@$(MAKE) fclean -C $(LFT_DIR) --no-print-directory
	@rm -rf *.bmp
	@rm -rf ${MLX_NAME}
	@rm -rf ${MLX_NAME}
	@rm -rf ${NAME}
	@echo "${NAME} has been deleted"

clean_bonus:
	@rm -rf $(OBJ_DIR)/*.o

bonus: clean_bonus 
	@$(MAKE) BONUS="-D BONUS" BSRC="TRUE" all --no-print-directory

re: fclean all