# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 09:52:55 by cborrome          #+#    #+#              #
#    Updated: 2025/06/12 10:22:30 by cborrome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3d
NAME_BONUS  	= cub3d_bonus
NAME_DEBUG		= cub3d_debug
CC				= cc

CFLAGS			= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
CFLAGS_DEBUG	= -Wextra -Wall -Werror -g -O0 -fsanitize=address
LIBMLX			= ./MLX42

HEADERS			= -I$(LIBMLX)/include -Isrc

LIBS = $(LIBMLX)/build/libmlx42.a \
		./glfw/build/src/libglfw3.a \
		-ldl -pthread -lm \
		-lX11 -lXrandr -lXcursor -lXi -lXxf86vm -lXinerama -lXext


SRCS	=	./src/main.c \
			./src/arena.c \
			./src/simple_exit.c \
			./src/01checks/check_map.c \
			./src/01checks/check_map_content.c \
			./src/01checks/info_search.c \
			./src/01checks/info_search_2.c \
			./src/01checks/color_check.c \
			./src/01checks/find_path_color.c \
			./src/01checks/map_requirements_check.c \
			./src/02player/player_movement.c \
			./src/02player/player_utils.c \
			./src/03rendering/rendering.c \
			./src/03rendering/dda.c \
			./src/03rendering/raycasting.c \
			./src/03rendering/texture.c \
			./src/03rendering/mini_map.c \
			./src/utils.c \
			./src/utils02.c \
			./src/utils03.c \
			./gnl_cub3d/get_next_line_bonus.c \
			./gnl_cub3d/get_next_line_utils_bonus.c \


BSRCS	=	./src/main.c \
			./src/arena.c \
			./src/simple_exit.c \
			./src/01checks/check_map.c \
			./src/01checks/check_map_content.c \
			./src/01checks/info_search.c \
			./src/01checks/info_search_2.c \
			./src/01checks/color_check.c \
			./src/01checks/find_path_color.c \
			./src/01checks/map_requirements_check.c \
			./src/02player/player_movement.c \
			./src/02player/player_utils.c \
			./src/03rendering/rendering.c \
			./src/03rendering/dda.c \
			./src/03rendering/texture.c \
			./src/utils.c \
			./src/utils02.c \
			./src/utils03.c \
			./gnl_cub3d/get_next_line_bonus.c \
			./gnl_cub3d/get_next_line_utils_bonus.c \

OBJS	=	$(SRCS:%.c=%.o)
BOBJ	=	$(BSRCS:%.c=%.o)

REPO_URL=https://github.com/codam-coding-college/MLX42.git
REPO_DIR=MLX42
GLFW_URL=https://github.com/glfw/glfw.git
GLFW_DIR=glfw

all: clone clone_glfw libglfw libmlx $(NAME)

bonus: clone clone_glfw libglfw libmlx $(NAME_BONUS)

debug: CFLAGS=$(CFLAGS_DEBUG)
debug: clean clone clone_glfw libglfw libmlx $(NAME_DEBUG)

clone:
	@if [ ! -d "$(REPO_DIR)" ]; then \
		git clone $(REPO_URL) $(REPO_DIR); \
	else \
		echo "$(REPO_DIR) already exists."; \
	fi

clone_glfw:
	@if [ ! -d "$(GLFW_DIR)" ]; then \
		git clone $(GLFW_URL) $(GLFW_DIR); \
	else \
		echo "$(GLFW_DIR) already exists."; \
	fi

libglfw:
	@if [ ! -f $(GLFW_DIR)/build/src/libglfw3.a ]; then \
		cmake $(GLFW_DIR) -B $(GLFW_DIR)/build -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF && make -C $(GLFW_DIR)/build -j4; \
	else \
		echo "libglfw already built."; \
	fi
	
libmlx:
	@if [ ! -f $(LIBMLX)/build/libmlx42.a ]; then \
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	else \
		echo "libmlx already built."; \
	fi

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME_BONUS): $(BOBJ)
	@$(CC) $(BOBJ) $(LIBS) $(HEADERS) -o $(NAME_BONUS)

$(NAME_DEBUG): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -fsanitize=address -o $(NAME_DEBUG)

clean:
	@rm -rf $(LIBMLX)/build
	@rm -rf $(GLFW_DIR)/build
	@rm -rf $(OBJS) $(BOBJ) $(DEBUG_OBJS)

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS) $(NAME_DEBUG)
	@rm -rf $(LIBMLX)/build
	@rm -rf $(GLFW_DIR)/build
	@rm -rf $(REPO_DIR)
	@rm -rf $(GLFW_DIR)
	@rm -rf $(OBJS) $(BOBJ) $(DEBUG_OBJS)

re: fclean all bonus

.PHONY: all clean fclean re bonus debug clone clone_glfw libmlx libglfw