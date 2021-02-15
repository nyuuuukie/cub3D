NAME = libft.a
CC = gcc

CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./

SOURCES =	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
			ft_isprint.c ft_memccpy.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
			ft_strlcat.c ft_strncmp.c ft_strcmp.c ft_strrchr.c ft_tolower.c ft_toupper.c \
			ft_memcmp.c ft_memchr.c ft_strlcpy.c  ft_strnstr.c  ft_calloc.c  ft_strdup.c \
			ft_putstr_fd.c ft_putendl_fd.c  ft_putnbr_fd.c  ft_putchar_fd.c  ft_itoa.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_split.c ft_strlen.c 
			
BONUS_SRC = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstadd_back.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstclear.c \
			ft_lstmap.c 

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(BONUS_SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $@ $^
	ranlib $@
	@echo 'created successfully'

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

clean: 
	rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -rf $(NAME)
	
re: fclean all 

bonus: $(OBJECTS) $(OBJECTS_BONUS)
	@ar rc $(NAME) $?
	@ranlib $(NAME)
	@echo $(NAME) 'created with bonuses'

.PHONY: all clean fclean re bonus