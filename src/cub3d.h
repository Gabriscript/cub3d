#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include "arena.h"
# include <MLX42/MLX42.h>
# include <stdlib.h> //exit

# define SUCCESS 0
# define FAILURE 1
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct s_game
{
	char	**map;
	int		height;
	int		end_of_map;
	char	**file;
	mlx_t 	*mlx; 
	t_arena *arena;
}	t_game;

void	ft_map_name(char *argv);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
void	simple_exit(t_game *game);
int		ft_strlen(char *str);
int		ft_strcmp(const char *main, const char *compared);
void	ft_putstr_fd(char *str, int fd);
bool	is_valid_file(char *file, bool cub);
int		ft_isspace(char c);
bool	map_has_all_component(t_game *game);
bool 	is_map_at_end(t_game *game);
bool	is_surrounded(t_game *game);
void	key_hook(mlx_key_data_t keydata, void* param);
void	close_window(void *param);
int		init_mlx_window(t_game *game);

#endif