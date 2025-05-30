#include "cub3d.h"

void	divede_cub_file(t_game *game)
{
	int	i;
	// int	map_len;
	// int	info_len;

	i = game->file.total_file_len;
	printf("[DEBUG] in divide_cup_file.c int i INIZIALE: %d\n", i); //debug
	
	while(game->file.full_file_one_line[i] == '1' || \
		game->file.full_file_one_line[i] == '0' || \
		game->file.full_file_one_line[i] == ' ' || \
		game->file.full_file_one_line[i] == '\n' || \
		game->file.full_file_one_line[i] == 'N' || \
		game->file.full_file_one_line[i] == 'S' || \
		game->file.full_file_one_line[i] == 'W' || \
		game->file.full_file_one_line[i] == 'E' || \
		game->file.full_file_one_line[i] == EOF)
		i--;
	printf("[DEBUG] in divide_cup_file.c int i FINALE: %d\n", i); //debug
	
	printf("[DEBUG] in divide_cup_file.c char in the map: \n%c\n", game->file.full_file_one_line[i]); //debug
	
	}
