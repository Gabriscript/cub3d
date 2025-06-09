#include "cub3d.h"
void	map_allowed_char_check(char *map_str, t_game *game)
{
	int	x;

	x = 0;
	while (map_str[x])
	{
		if (map_str[x] != 'N' && map_str[x] != 'S' && map_str[x] != 'W' && \
			map_str[x] != 'E' && map_str[x] != '0' && map_str[x] != '1' && \
			map_str[x] != ' ' && map_str[x] != '\n')
			simple_exit("Error\nInvalid map\n", game);
		x++;
	}
	
}

void	find_player(t_game *game)
{
	int	row;
	int	col;

	game->file.map_matrix_flood_fill = \
			ft_split(game->file.full_map_flood_fill, '\n', game);
	row = 0;
	col = 0;
	while (game->file.map_matrix_flood_fill[row])
	{

		
		col = 0;
		while (game->file.map_matrix_flood_fill[row][col])
		{

		// printf("map_flood[%d row][%d col]\n", row, col);//

			if (game->file.map_matrix_flood_fill[row][col] == 'N' || \
				game->file.map_matrix_flood_fill[row][col] == 'S' || \
				game->file.map_matrix_flood_fill[row][col] == 'W' || \
				game->file.map_matrix_flood_fill[row][col] == 'E')
				{
					game->file.start_position_row = row;
					game->file.start_position_col = col;
					// printf("FIND PLAYER ROW %d\n", game->file.start_position_row);//
// printf("FIND PLAYER COL %d\n", game->file.start_position_col);//
				}
				col++;
		}
		row++;
	}
	game->file.total_rows = row;
}

void	map_validation_flood_fill(t_game *game, char **map_flood, int row, int col)
{
// printf("PLAYER ROW %d\n", game->file.start_position_row);
// printf("PLAYER COL %d\n", game->file.start_position_col);
// printf("map_flood[%d row][%d col]\n", row, col);
	if (col && col - 1 < 0)
		simple_exit("Error\nNot a valid map_COL-1 \n", game);//
	if (row && row - 1 < 0)
		simple_exit("Error\nNot a valid map_ROW-1 \n", game);//
	if (row && row + 1 > game->file.total_rows)
		simple_exit("Error\nNot a valid map_ROW+1 \n", game);//
	if (!map_flood[row][col])
		simple_exit("Error\nNot a valid map_FLOOD\n", game);//
	if (map_flood[row][col] == '1' || map_flood[row][col] == 'V')
		return ;
	map_flood[row][col] = 'V';
	map_validation_flood_fill(game, map_flood, row, col + 1);
	map_validation_flood_fill(game, map_flood, row, col - 1);
	map_validation_flood_fill(game, map_flood, row + 1, col);
	map_validation_flood_fill(game, map_flood, row - 1, col);
}
/*
void	map_zero_check(t_game *game)
{
// 	for(int i = 0; game->file.map_matrix[i]; i++)
// 		printf("[DEBUG] %s\n", game->file.map_matrix[i]);
	int	x;
// printf("[DEBUG] full_map_zero_check \n%s\n", game->file.full_map_zero_check);
	x = 0;
	while (game->file.full_map_zero_check[x])//trasforma il  player in 0 per il zero check.
	{
		if (game->file.full_map_zero_check[x] == 'N' || \
			game->file.full_map_zero_check[x] == 'S' || \
			game->file.full_map_zero_check[x] == 'W' || \
			game->file.full_map_zero_check[x] == 'E')
			game->file.full_map_zero_check[x] = '0';
		x++;
	}
// printf("[DEBUG] full_map_zero_check \n%s\n", game->file.full_map_zero_check);
	game->file.map_matrix_zero_check = \
		ft_split(game->file.full_map_zero_check, '\n', game);
		
		
		// for(int i = 0; game->file.map_matrix_zero_check[i]; i++)
		// printf("[DEBUG] %s\n", game->file.map_matrix_zero_check[i]);

	int	i;
	int	y;
	// char **zero;
	i = 0;
	y = 0;
	// zero = game->file.map_matrix_zero_check;
	while (game->file.map_matrix_zero_check[i])
	{
		while (game->file.map_matrix_zero_check[i][y])
		{
			//check i-1 < 0 || y -1 < 0 ERROR, NOT A proper map.
			//forse e' piu semplice controllare i bordi ma la mappa puo non essere rettangolare.
			if (game->file.map_matrix_zero_check[i][y] == '0')
				if (!game->file.map_matrix_zero_check[i-1][y-1])
				// || \
				//	game->file.map_matrix_zero_check[i-1][y-1] != '1' || game->file.map_matrix_zero_check[i-1][y-1] != '0')
				{
					simple_exit("Error\nHERE\nInvalid map\n", game);
				}
			y++;
		}
		
		i++;
	}
}
*/