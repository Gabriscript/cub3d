#include "cub3d.h"

static void	color_path_check(char *path, t_game *game)
{
	int	x;
	int	comma_counter;
	int	number_counter;

	x = 0;
	comma_counter = 0;
	number_counter = 0;
	while (path[x])
	{
		if (path[x] == ',')
			comma_counter += 1;
		if (path[x] >= '0' || path[x] <= 9)
			number_counter += 1;
		x++;
	}
	if (comma_counter > 2 || number_counter > 9)
		simple_exit("Error\nInvalid color path\n", game);
}

void	color_check(t_game *game)
{
	char	**f_color;
	char	**c_color;

	color_path_check(game->file.f_path, game);
	color_path_check(game->file.c_path, game);
	f_color = ft_split(game->file.f_path, ',', game);
	c_color = ft_split(game->file.c_path, ',', game);
	game->floor[0] = ft_simple_atoi(f_color[0], game);
	game->floor[1] = ft_simple_atoi(f_color[1], game);
	game->floor[2] = ft_simple_atoi(f_color[2], game);
	game->ceiling[0] = ft_simple_atoi(c_color[0], game);
	game->ceiling[1] = ft_simple_atoi(c_color[1], game);
	game->ceiling[2] = ft_simple_atoi(c_color[2], game);
	if (game->floor[0] > 255 || game->floor[1] > 255 || game->floor[2] > 255
		|| game->ceiling[0] > 255 || game->ceiling[1] > 255
		|| game->ceiling[2] > 255)
		simple_exit("Error\nInvalid color\n", game);
}
