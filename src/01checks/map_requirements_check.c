#include "cub3d.h"

void	map_allowed_char_check(char *map_str, t_game *game)
{
	int	x;

	x = 0;
	while (map_str[x])
	{
		if (map_str[x] != 'N' && map_str[x] != 'S' && map_str[x] != 'W'
			&& map_str[x] != 'E' && map_str[x] != '0' && map_str[x] != '1'
			&& map_str[x] != ' ' && map_str[x] != '\n')
			simple_exit("Error\nInvalid map\n", game);
		x++;
	}
}

void	map_new_lines_check(char *map_str, t_game *game)
{
	int	i;

	i = 0;
	while (map_str[i + 1] && (map_str[i] == ' ' || map_str[i] == '\n'))
		i++;
	while (map_str[i] && map_str[i + 1])
	{
		if (map_str[i] == '\n' && map_str[i + 1] == '\n')
			simple_exit("Error\nInvalid map\n", game);
		if (map_str[i] == '\n' && map_str[i + 1] == ' ')
		{
			while (map_str[i + 2] && map_str[i + 1] == ' '
				&& (map_str[i + 2] == ' ' || map_str[i + 2] == '\n'))
			{
				if (map_str[i + 2] == '\n')
					simple_exit("Error\nInvalid map\n", game);
				i++;
			}
		}
		i++;
	}
}

void	find_player(t_game *game)
{
	int	row;
	int	col;

	game->file.map_matrix_flood_fill = ft_split
		(game->file.full_map_flood_fill, '\n', game);
	row = 0;
	col = 0;
	while (game->file.map_matrix_flood_fill[row])
	{
		col = 0;
		while (game->file.map_matrix_flood_fill[row][col])
		{
			if (game->file.map_matrix_flood_fill[row][col] == 'N' ||
				game->file.map_matrix_flood_fill[row][col] == 'S' ||
				game->file.map_matrix_flood_fill[row][col] == 'W' ||
				game->file.map_matrix_flood_fill[row][col] == 'E')
			{
				game->file.start_position_row = row;
				game->file.start_position_col = col;
			}
			col++;
		}
		row++;
	}
	game->file.total_rows = row;
}

void	map_validation_flood_fill(t_game *game, char **map_flood,
		int row, int col)
{
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

void	space_to_wall(char **map_matrix)
{
	int	x;
	int	y;

	x = 0;
	while(map_matrix[x])
	{
		y = 0;
		while (map_matrix[x][y])
		{
			if (map_matrix[x][y] == ' ')
				map_matrix[x][y] = '0';
			y++;
		}
		x++;
	}
}
