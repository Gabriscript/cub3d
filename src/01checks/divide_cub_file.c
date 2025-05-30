#include "cub3d.h"

void	fill_full_line()
{
	
}

void	divede_cub_file(t_game *game)
{
	int	i;
	int	info_len;
	int	map_len;

	i = game->file.total_file_len - 1;
	printf("[DEBUG] in divide_cup_file.c int i INIZIALE: %d\n", i); //debug
	
	while(game->file.full_file_one_line[i] == '1' || \
		game->file.full_file_one_line[i] == '0' || \
		game->file.full_file_one_line[i] == ' ' || \
		game->file.full_file_one_line[i] == '\n' || \
		game->file.full_file_one_line[i] == 'N' || \
		game->file.full_file_one_line[i] == 'S' || \
		game->file.full_file_one_line[i] == 'W' || \
		game->file.full_file_one_line[i] == 'E')
			i--;
	printf("[DEBUG] in divide_cup_file.c int i FINALE: %d\n", i); //debug
	
	printf("[DEBUG] in divide_cup_file.c char in the map: \n%c\n", game->file.full_file_one_line[i]); //debug
	info_len = i +1; //game->file.total_file_len - 1 - i;
	printf("[DEBUG] in divide_cup_file.c info len: %d\n", info_len); //debug
	map_len = game->file.total_file_len - 1 - info_len;
	printf("[DEBUG] in divide_cup_file.c map len: %d\n", map_len); //debug
	game->file.full_info = arena_alloc(game->arena, info_len + 1);
	game->file.full_map = arena_alloc(game->arena, map_len + 1);
	// fill_full_info();
	// fill_full_map();
}
