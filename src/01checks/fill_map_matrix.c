#include "cub3d.h"

void	fill_map_matrix(t_game *game)
{
	game->file.map_matrix = ft_split(game->file.full_map, '\n', game);
	// for(int x = 0; game->file.full_map[x]; x++)
	// 	printf("[DEBUG] in fill_map_matrix.c MAP MATRIX: \n%s\n", game->file.map_matrix[x]); //debug
}