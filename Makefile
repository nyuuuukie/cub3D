.PHONY: all clean fclean re bonus libft create_obj_dir

NAME = cub3D
LIBFT_NAME = libft.a

######################### CC && FLAGS ########################
CC = gcc

CFLAGS			= -Wall -Wextra -Werror
LIB_FLAGS		= -L $(LIBFT_DIR) -lft
INCLUDE_FLAGS 	= -I $(INCLUDES_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR)

######################### DIRECTORIES ########################
INCLUDES_DIR = include
LIBFT_DIR 	 = libft
GNL_DIR		 = get_next_line
SRC_DIR		 = src
OBJ_DIR		 = obj

######################### SOURCES ############################
SOURCES =	main.c \
			check_arguments.c \
			parse_map.c \
			errors.c \
			parse_scene_file.c \
			arrays.c \
			map_validation.c
		
GNL_SRC = 	gnl.c

######################## OBJECT FILES ########################
GNL_OBJ = $(addprefix $(OBJ_DIR)/, $(GNL_SRC:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

######################## HEADERS #############################
HEADERS = $(INCLUDES_DIR)/*.h

######################## INSTRUCTIONS ########################
all: libft create_obj_dir $(NAME)

create_obj_dir:
	@mkdir -p $(OBJ_DIR)

$(GNL_OBJ): $(GNL_DIR)/$(GNL_SRC)
	@$(CC) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

libft:
	@$(MAKE) bonus -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT_DIR)/$(LIBFT_NAME) $(GNL_OBJ)
	@$(CC) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

$(NAME): $(GNL_OBJ) $(OBJECTS) $(HEADERS)
	@$(CC) $(CFLAGS) $(GNL_OBJ) $(OBJECTS) $(LIB_FLAGS) -o $@
	@echo "$(NAME) created"

clean:
	@$(MAKE) clean -C $(LIBFT_DIR) --no-print-directory 
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	@rm -rf $(NAME)
	@echo "$(NAME) has been deleted"

re: fclean all