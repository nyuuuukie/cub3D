.PHONY: all clean fclean re bonus libft mlx create_dir

NAME = cub3D
LIBFT_NAME = libft.a
MLX_NAME = libmlx_Linux.a

######################### CC && FLAGS ########################

CC = gcc

CFLAGS			= -Wall -Wextra -Werror
MLX_FLAGS		= -L $(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
LIBFT_FLAGS		= -L $(LIBFT_DIR) -lft
INCLUDE_FLAGS 	= -I $(INCLUDES_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(MLX_DIR)

######################### DIRECTORIES ########################

SRC_DIR		 = src
OBJ_DIR		 = obj
MLX_DIR		 = mlx
LIBFT_DIR 	 = libft
INCLUDES_DIR = include
GNL_DIR		 = get_next_line

######################### SOURCES ############################

SOURCES =	main.c \
			check_arguments.c \
			parse_map.c \
			errors.c \
			parse_scene_file.c \
			arrays.c \
			map_validation.c \
			map.c
		
GNL_SRC = 	gnl.c

######################## OBJECT FILES ########################

GNL_OBJ = $(addprefix $(OBJ_DIR)/, $(GNL_SRC:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

######################## HEADERS #############################

HEADERS = $(INCLUDES_DIR)/*.h

######################## INSTRUCTIONS ########################
all: libft mlx create_dir $(NAME)

create_dir:
	@mkdir -p $(OBJ_DIR)

$(GNL_OBJ): $(GNL_DIR)/$(GNL_SRC)
	@$(CC) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

libft:
	@$(MAKE) bonus -C $(LIBFT_DIR) --no-print-directory

mlx:
	@$(MAKE) -C $(MLX_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT_DIR)/$(LIBFT_NAME) $(MLX_DIR)/$(MLX_NAME) $(GNL_OBJ)
	@$(CC) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

$(NAME): $(OBJECTS) $(GNL_OBJ) $(HEADERS) 
	@$(CC) $(CFLAGS) $(GNL_OBJ) $(OBJECTS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $@
	@echo "$(NAME) created"

clean:
	@$(MAKE) clean -C $(LIBFT_DIR) --no-print-directory 
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	@rm -rf $(NAME)
	@echo "$(NAME) has been deleted"

re: fclean all