/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:52:21 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 10:21:52 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <stdlib.h>

# define SUCCESS 0
# define FAILURE 1
# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 1200
# define SPEED 0.1
# define ROTATION_SPEED 0.05
# define M_PI 3.14159265358979323846
# define MINI_MAP 10
# define MINI_OFFSET 10
# define MINI_TILE_SIZE 10
# define PLAYER_SIZE 4

typedef struct s_file
{
	char	*full_file_one_line;
	char	*full_map;
	char	*full_map_flood_fill;
	int		total_file_len;
	int		total_rows;
	int		start_position;
	double	start_position_row;
	double	start_position_col;
	char	**map_matrix;
	char	**map_matrix_flood_fill;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*f_path;
	char	*c_path;
}	t_file;

typedef struct s_game
{
	mlx_t			*mlx;
	t_arena			*arena;
	t_file			file;
	mlx_image_t		*image;
	int				ceiling[3];
	int				floor[3];
	int				mini_size;
	char			*texture_files[4];
	int				color;

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
	double			player_x;
	double			player_y;
	double			player_angle;
}	t_game;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
}	t_ray;

//map
void		color_check(t_game *game);
int			find_color(t_game *game, int *i);
void		space_to_wall(char **map_matrix);
void		ft_map_name(char *argv);
void		ft_map_validation(char *argv, t_game *game);
void		find_player(t_game *game);
void		map_validation_flood_fill(t_game *game,
				char **map_flood, int row, int col);
void		info_search(t_game *s_game);
int			info_path_initial_letter(int *start, char *info_line);
int			find_path_1(t_game *game, int *i);
int			find_path_2(t_game *game, int *i);
int			find_color(t_game *game, int *i);
void		map_allowed_char_check(char *map_str, t_game *game);
void		map_new_lines_check(char *map_str, t_game *game);
//exit	
void		simple_exit(char *message, t_game *game);

//utils
bool		is_walkable(t_game *game, double x, double y);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
int			ft_strlen(char *str);
int			ft_strcmp(const char *main, const char *compared);
void		ft_putstr_fd(char *str, int fd);
int			ft_isspace(char c);
void		key_hook(mlx_key_data_t keydata, void *param);
void		close_window(void *param);
int			init_mlx_window(t_game *game);
int			create_rgba(int r, int g, int b, int a);
void		draw_mini_map(t_game *game);
char		**ft_split(char const *s, char c, t_game *game);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strdup_path(const char *s, t_game *game, int start, int end);
char		*ft_strdup_color(const char *s, t_game *game, int start, int end);
int			ft_simple_atoi(const char *str, t_game *game);
void		raycast(t_game *game);
void		rendering(t_game *game);
void		render_background(t_game *game);
void		init_player_position(t_game *game);
int			load_textures(t_game *game);
void		free_textures(t_game *game);
void		init_ray(t_game *game, t_ray *ray, int x);
void		calculate_wall_distance(t_game *game, t_ray *ray);
void		perform_dda(t_game *game, t_ray *ray);
int			get_texture_pixel(mlx_image_t *texture, int x, int y);
mlx_image_t	*load_single_texture(mlx_t *mlx, const char *path);
mlx_image_t	*get_wall_texture(t_game *game, t_ray *ray);

#endif
