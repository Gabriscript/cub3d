NAME        = so_long
NAME_BONUS = so_long_bonus
CC          = cc

CFLAGS      = -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBMLX      = ./MLX42

LIBFT       = ./src/libft_project
PRINTF      = ./src/printf_project

HEADERS     = -Isrc/libft_project -I$(LIBMLX)/include -Isrc/printf_project -Isrc
LIBS        = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm \
               $(LIBFT)/libft.a \
               $(PRINTF)/libftprintf.a

SRCS	=	./src/main.c \
			./src/validation.c \
			./src/validation_2.c \
			./src/error_messages.c \
			./src/struct_initialisation.c \
			./src/map_check.c \
			./src/start_graphic.c \
			./src/memory.c \
			./src/movement.c \

BSRCS	=	./src/main_bonus.c \
			./src/validation_bonus.c \
			./src/validation_2_bonus.c \
			./src/error_messages_bonus.c \
			./src/struct_initialisation_bonus.c \
			./src/map_check_bonus.c \
			./src/start_graphic_bonus.c \
			./src/memory_bonus.c \
			./src/movement_bonus.c \

OBJS	=	$(SRCS:%.c=%.o)
BOBJ    =   $(BSRCS:%.c=%.o)

REPO_URL=https://github.com/codam-coding-college/MLX42.git
REPO_DIR=MLX42

all: clone libmlx $(NAME)

bonus: clone libmlx $(NAME_BONUS)

clone:
	@if [ ! -d "$(REPO_DIR)" ]; then \
		git clone $(REPO_URL) $(REPO_DIR); \
	else \
		echo "$(REPO_DIR) already exists."; \
	fi
	
libmlx:
	@if [ ! -f $(LIBMLX)/build/libmlx42.a ]; then \
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	else \
		echo "libmlx already built."; \
	fi

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
$(BOBJ): %.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling bonus: $(notdir $<)\n"

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(PRINTF)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME_BONUS): $(BOBJ)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(PRINTF)
	@$(CC) $(BOBJ) $(LIBS) $(HEADERS) -o $(NAME_BONUS)

clean:
	@rm -rf $(LIBMLX)/build
	@rm -rf $(OBJS) $(BOBJ)

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@rm -rf $(LIBMLX)/build
	$(MAKE) -C $(LIBFT) fclean
	$(MAKE) -C $(PRINTF) fclean
	@rm -rf $(REPO_DIR)
	@rm -rf $(OBJS) $(BOBJ)

re: fclean all bonus
	
.PHONY: all clean fclean re bonus clone libmlx
