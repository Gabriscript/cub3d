#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include "arena.h"
# include "get_next_line_bonus.h"
# include <MLX42/MLX42.h>
# include <stdlib.h> //exit

# define SUCCESS 0
# define FAILURE 1
# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 1200
# define SPEED 0.1
# define ROTATION_SPEED 0.05
# define M_PI 3.14159265358979323846
# define MINI_MAP 10
# define MINI_OFFSET 10



typedef struct s_file
{
	char	*full_file_one_line;
	char	*full_map;
	char	*full_info;
	int		total_file_len;
	int		total_rows;
	int		start_position;
	char	**map_matrix;
	char	**map_matrix_flood;
}	t_file;

typedef struct s_game
{
	char	**map;  //serve?
	int		height; //serve?
	int		end_of_map;  //serve?
	// char	**file; //serve? se si va cambiato il nome
	mlx_t 	*mlx; 
	t_arena *arena;
	t_file	file;
	mlx_image_t *image;
	int		ceiling[3];
	int		floor[3];
	int		mini_size;

	// Texture PNG per i muri
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	
	// Immagini MLX delle texture
	mlx_image_t		*north_img;
	mlx_image_t		*south_img;
	mlx_image_t		*east_img;
	mlx_image_t		*west_img;
	
	// Posizione del giocatore
	double		player_x;
	double		player_y;
	double		player_angle;
}	t_game;

//map
void	ft_map_name(char *argv);
bool	map_has_all_component(t_game *game);
bool 	is_map_at_end(t_game *game);
void	ft_map_validation(char *argv, t_game *game);
bool	is_surrounded(t_game *game);
void	divede_cub_file(t_game *game);

//exit
void	simple_exit(t_game *game);

//utils
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(char *str);
int		ft_strcmp(const char *main, const char *compared);
void	ft_putstr_fd(char *str, int fd);
int		ft_isspace(char c);
void	key_hook(mlx_key_data_t keydata, void* param);
void	close_window(void *param);
int		init_mlx_window(t_game *game);
int		create_rgba(int r, int g, int b, int a);
void	draw_mini_map(t_game *game);

void	*ft_memcpy(void *dst, const void *src, size_t n);


//test - to be removed
#endif