#include "cub3d.h"

static void	info_checks(t_game *game)
{
	if (game->file.NO != 1 || game->file.SO != 1 || \
			game->file.WE != 1 || game->file.EA != 1 || game->file.F != 1 \
			|| game->file.C != 1)
			{
				ft_putstr_fd("Error\nIncorrect identifier number\n", 2);
				simple_exit(game);
				exit (EXIT_FAILURE);
			}
}

void	info_search(t_game *game)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while(game->file.full_file_one_line[i])
	{
		if (game->file.NO == 1 && game->file.SO == 1 && \
			game->file.WE == 1 && game->file.EA == 1 && game->file.F == 1 \
			&& game->file.C == 1)
				if (y == 0)
					y = i;
		while (game->file.full_file_one_line[i] == '\n' ||
			   game->file.full_file_one_line[i] == ' ')
			i++;
		if (find_path_1(game, &i) == 1)
			continue;
		else if (find_path_2(game, &i) == 1)
			continue;
		else if (find_color(game, &i) == 1)
			continue;
		i++;
	}
	info_checks(game);
	divide_cub_file(game, &y);
}


/*
example of info:
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
*/