.PHONY: all clean fclean re bonus libft mlx create_dir

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
			parse_map.c \
			errors.c \
			parse_scene_file.c \
			arrays.c \
			map_validation.c \
			map_utils.c \
			vector.c \
			raycasting.c \
			key_action.c \
			engine_move.c \
			engine.c \
			init.c \
			init_ext.c \
			colors.c\
			angle_radian.c\
			music.c \
			save.c

B_SOURCES = 

GNL_SRC = 	get_next_line.c

######################## OBJECT FILES ########################

GNL_OBJ = $(addprefix $(OBJ_DIR)/, $(GNL_SRC:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

######################## HEADERS #############################

HEADERS = $(INC_DIR)/*.h

######################## INSTRUCTIONS ########################


r: all
	./${NAME} ${MAP}

s: all
	./${NAME} ${MAP} --save

br: bonus
	./${NAME} ${MAP}

bs: bonus
	./${NAME} ${MAP} --save

bdebug:
	$(MAKE) DEBUG="-g" br MAP=${MAP}

debug:
	$(MAKE) DEBUG="-g" r MAP=${MAP}

all: libft mlx create_dir $(ACT_DIR) $(NAME)

create_dir:
	@mkdir -p $(OBJ_DIR)

$(GNL_OBJ): $(GNL_DIR)/$(GNL_SRC)
	@$(CC) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

libft:
	@$(MAKE) bonus -C $(LFT_DIR) --no-print-directory

mlx:
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@cp $(MLX_DIR)/$(MLX_NAME) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LFT_DIR)/$(LIBFT_NAME) $(MLX_DIR)/$(MLX_NAME) $(GNL_OBJ)
	@$(CC) $(DEBUG) $(BONUS) $(OS_FLAG) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

$(NAME): $(OBJECTS) $(GNL_OBJ) $(HEADERS) 
	@$(CC) $(DEBUG) $(BONUS) $(CFLAGS) $(GNL_OBJ) $(OBJECTS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $@
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