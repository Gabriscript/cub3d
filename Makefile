NAME        = cub3d
NAME_BONUS = cub3d_bonus
CC          = cc

CFLAGS      = -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBMLX      = ./MLX42

HEADERS     = -Isrc/libft_project -I$(LIBMLX)/include -Isrc/printf_project -Isrc
LIBS        = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	=	./src/main.c \
			./src/arena.c \
			./src/check.c \
			./src/utils.c \


BSRCS	=	./src/main.c \
			./src/arena.c \
			./src/check.c \
			./src/utils.c \

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
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
$(BOBJ): %.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME_BONUS): $(BOBJ)
	@$(CC) $(BOBJ) $(LIBS) $(HEADERS) -o $(NAME_BONUS)

clean:
	@rm -rf $(LIBMLX)/build
	@rm -rf $(OBJS) $(BOBJ)

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@rm -rf $(LIBMLX)/build
	@rm -rf $(REPO_DIR)
	@rm -rf $(OBJS) $(BOBJ)

re: fclean all bonus
	
.PHONY: all clean fclean re bonus clone libmlx
