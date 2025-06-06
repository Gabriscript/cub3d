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

void	map_zero_check(t_game *game)
{
// 	for(int i = 0; game->file.map_matrix[i]; i++)
// 		printf("[DEBUG] %s\n", game->file.map_matrix[i]);
	int	x;
// printf("[DEBUG] full_map_zero_check \n%s\n", game->file.full_map_zero_check);
	x = 0;
	while (game->file.full_map_zero_check[x])
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
				if (!game->file.map_matrix_zero_check[i-1][y-1])/* || \
					game->file.map_matrix_zero_check[i-1][y-1] != '1' || \
					game->file.map_matrix_zero_check[i-1][y-1] != '0')*/
				{
					simple_exit("Error\nHERE\nInvalid map\n", game);
				}
			y++;
		}
		
		i++;
	}
	


}
