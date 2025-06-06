#include "cub3d.h"

// static void	fill_full_info(t_game *game, int info_len)
// {
// 	ft_memcpy(game->file.full_info, game->file.full_file_one_line, info_len);
// 	game->file.full_info[info_len] = '\0';
// }

// static void	fill_full_map(t_game *game, int map_len, int info_len)
// {
// 	ft_memcpy(game->file.full_map, game->file.full_file_one_line + info_len, map_len);
// 	game->file.full_map[map_len] = '\0';
// }
/*
// static int	last_char_check(t_game *game, int i)
// {
// 	i = i + 1;
// 	while(game->file.full_file_one_line[i] == ' ' || \
// 		game->file.full_file_one_line[i] == '\n')
// 		i++;
// 	if (game->file.full_file_one_line[i] == 'N' || \
// 	game->file.full_file_one_line[i] == 'S' || \
// 	game->file.full_file_one_line[i] == 'W' || \
// 	game->file.full_file_one_line[i] == 'E' || \
// 	game->file.full_file_one_line[i] == '0')
// 	{
// 	ft_putstr_fd("Error\nNot a proper map\n", 2);
// 	simple_exit(game);
// 	exit (EXIT_FAILURE);
// 	}
// 	return(i);
// }
*/
/*
// static int	first_char_map(t_game *game, int i)
// {
// 	i = i + 1;
// 	while(game->file.full_file_one_line[i] != '1')
// 	{
// 		if (game->file.full_file_one_line[i] == 'N' || \
// 			game->file.full_file_one_line[i] == 'S' || \
// 			game->file.full_file_one_line[i] == 'W' || \
// 			game->file.full_file_one_line[i] == 'E' || \
// 			game->file.full_file_one_line[i] == '0')
// 			{
// 			ft_putstr_fd("Error\nNot a proper map\n", 2);
// 			simple_exit(game);
// 			exit (EXIT_FAILURE);
// 			}
// 		i++;
// 	}
// 	while (game->file.full_file_one_line[i] != '\n')
// 		i--;	
// 	return(i);
// }
*/

static void	map_len_check(t_game *game)
{
	if (ft_strlen(game->file.full_map) < 11)
	{
		ft_putstr_fd("Error\nNot a proper map\n", 2);
		simple_exit(game);
		exit (EXIT_FAILURE);
	}
}
/*
// void	divede_cub_file(t_game *game)
// {
// 	int	i;
// 	int	info_len;
// 	int	map_len;

// 	i = game->file.total_file_len - 1;	
// 	while(game->file.full_file_one_line[i] == '1' || \
// 		game->file.full_file_one_line[i] == '0' || \
// 		game->file.full_file_one_line[i] == ' ' || \
// 		game->file.full_file_one_line[i] == '\n' || \
// 		game->file.full_file_one_line[i] == 'N' || \
// 		game->file.full_file_one_line[i] == 'S' || \
// 		game->file.full_file_one_line[i] == 'W' || \
// 		game->file.full_file_one_line[i] == 'E')
// 			i--;
// 		info_len = i;
// 		game->file.full_info = arena_alloc(game->arena, info_len + 1);
// 		fill_full_info(game, info_len);
// 		printf("[DEBUG] in divide_cup_file.c TOTAL file len: %d\n", game->file.total_file_len); //debug
		
// 		// i = last_char_check(game, i);
// 		i = first_char_map(game, i);
// 		map_len = game->file.total_file_len - info_len;
// // printf("[DEBUG] in divide_cup_file.c map len: %d\n", map_len); //debug

// 	game->file.full_map = arena_alloc(game->arena, map_len + 1);
// 	fill_full_map(game, map_len, info_len);
// 	map_len_check(game);

// printf("[DEBUG] in divide_cup_file.c full_info: \n%s\n", game->file.full_info); //debug
// printf("[DEBUG] in divide_cup_file.c full_map: \n%s\n", game->file.full_map); //debug

// }
*/

void	divide_cub_file(t_game *game, int *y)
{
	int	map_len;

	map_len = game->file.total_file_len - (*y);
	game->file.full_map = arena_alloc(game->arena, map_len + 1);
	ft_memcpy(game->file.full_map, game->file.full_file_one_line + (*y), map_len);
	game->file.full_map[map_len] = '\0';
	map_len_check(game);
}