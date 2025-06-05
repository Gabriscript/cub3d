#include "cub3d.h"

void	recover_path(t_game *game, t_file *file, int *i)
{
	int	path_len;

	path_len = 0;
	if (file->NO > 1 || file->SO > 1 || file->WE > 1 || file->EA > 1)
	{
		ft_putstr_fd("Error\nToo many identifier\n", 2);
		simple_exit(game);
		exit (EXIT_FAILURE);
	}
	i += 2; //salto NO per esempio
	while(game->file.full_file_one_line[i] == ' ')
		i++;
	if (game->file.full_file_one_line[i] == '\n')
	{
		ft_putstr_fd("Error\nEmpty path\n", 2);
		simple_exit(game);
		exit (EXIT_FAILURE);
	}
	else
	{
		while(game->file.full_file_one_line[i] != '\n')
			path_len++;
		
		ft_strndup(game->file.full_file_one_line, game, i, path_len);
		i = i + path_len;
	}

}

void	find_path(t_game *game, int *i)
{
	if (game->file.full_file_one_line[i] == 'N' && \
		game->file.full_file_one_line[i + 1] == 'O')
		{
			game->file.NO += 1;
			recover_path(game, game->file, &i);
		}
	if (game->file.full_file_one_line[i] == 'S' && \
		game->file.full_file_one_line[i + 1] == 'O')
		{
			game->file.SO += 1;
			recover_path(game, game->file, &i);
		}
	if (game->file.full_file_one_line[i] == 'W' && \
		game->file.full_file_one_line[i + 1] == 'E')
		{
			game->file.WE += 1;
			recover_path(game, game->file, &i);
		}
	if (game->file.full_file_one_line[i] == 'E' && \
		game->file.full_file_one_line[i + 1] == 'A')
		{
			game->file.EA += 1;
			recover_path(game, game->file, &i);
		}
}

static void	find_color(t_game *game, int *i)
{
	if (game->file.full_file_one_line[i] == 'F')
			recover_color('F', game);
	if (game->file.full_file_one_line[i] == 'C')
			recover_color('C', game);
}

void	info_search(t_game *s_game)
{
	int	i;

	i = 0;
	while((game->file.full_file_one_line[i])
	{
		find_path(game, &i);
		find_color(game), &i;

		i++;
	}
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