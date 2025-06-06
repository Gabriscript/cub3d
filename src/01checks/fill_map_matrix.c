#include "cub3d.h"

void	fill_map_matrix(t_game *game)
{
	game->file.map_matrix = ft_split(game->file.full_map, '\n', game);

	// for (int i = 0; game->file.map_matrix[i] != NULL; i++)//debug
	// {//debug
	// 	printf("[DEBUG] in fill_map_matrix.c Row %d: %s\n", i, game->file.map_matrix[i]);//debug
	// 	for (int j = 0; game->file.map_matrix[i][j] != '\0'; j++)//debug
	// 		printf("Char at [%d][%d]: %c\n", i, j, game->file.map_matrix[i][j]); //debug
	// }//debug
}