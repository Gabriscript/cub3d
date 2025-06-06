#include "cub3d.h"

char	*recover_path(t_game *game, t_file *file, int *i)
{
	int	path_start;
	char	*path;
	printf("[DEBUG] in info_search.c number of NO: %d\n", game->file.NO);//debug
	printf("[DEBUG] in info_search.c number of SO: %d\n", game->file.SO);//debug
	printf("[DEBUG] in info_search.c number of WE: %d\n", game->file.WE);//debug
	printf("[DEBUG] in info_search.c number of EA: %d\n", game->file.EA);//debug
	if (file->NO > 1 || file->SO > 1 || file->WE > 1 || file->EA > 1)
	{
		ft_putstr_fd("Error\nToo many path identifier\n", 2);
		simple_exit(game);
		exit (EXIT_FAILURE);
	}
	*i += 2; //salto NO per esempio
	while(game->file.full_file_one_line[*i] == ' ')
		(*i)++;
	if (game->file.full_file_one_line[*i] == '\n')
	{
		ft_putstr_fd("Error\nEmpty path\n", 2);
		simple_exit(game);
		exit (EXIT_FAILURE);
	}
	path_start = *i;
	while(game->file.full_file_one_line[*i] != '\n')
		(*i)++;
	path = ft_strdupline(game->file.full_file_one_line, game, path_start, *i);
	(*i) = (*i) + 1;
	return(path);
}

int	find_path_1(t_game *game, int *i)
{
	if (game->file.full_file_one_line[*(i)] == 'N' && \
		game->file.full_file_one_line[*(i) + 1] == 'O')
		{
			game->file.NO += 1;
			game->file.NO_path = recover_path(game, &game->file, i);
			return(1);
		}
	else if (game->file.full_file_one_line[*(i)] == 'S' && \
		game->file.full_file_one_line[*(i) + 1] == 'O')
		{
			game->file.SO += 1;
			game->file.SO_path = recover_path(game, &game->file, i);
			return(1);
		}
	return(0);
}

int	find_path_2(t_game *game, int *i)
{
	if (game->file.full_file_one_line[*(i)] == 'W' && \
		game->file.full_file_one_line[*(i) + 1] == 'E')
		{
			game->file.WE += 1;
			game->file.WE_path = recover_path(game, &game->file, i);
			return(1);
		}
	else if (game->file.full_file_one_line[*(i)] == 'E' && \
		game->file.full_file_one_line[*(i) + 1] == 'A')
		{
			game->file.EA += 1;
			game->file.EA_path = recover_path(game, &game->file, i);
			return(1);
		}
	return(0);
}
static char	*recover_color(t_game *game, t_file *file, int *i)
{
	int	color_start;
	char	*path;
	printf("[DEBUG] in info_search.c number of F: %d\n", game->file.F);//debug
	printf("[DEBUG] in info_search.c number of C: %d\n", game->file.C);//debug
	
	if (file->F > 1 || file->C > 1)
	{
		ft_putstr_fd("Error\nToo many color identifier\n", 2);
		simple_exit(game);
		exit (EXIT_FAILURE);
	}
	*i += 2; //salto NO per esempio
	while(game->file.full_file_one_line[*i] == ' ')
		(*i)++;
	if (game->file.full_file_one_line[*i] == '\n')
	{
		ft_putstr_fd("Error\nEmpty color\n", 2);
		simple_exit(game);
		exit (EXIT_FAILURE);
	}
	color_start = *i;
	while(game->file.full_file_one_line[*i] != '\n')
		(*i)++;
	path = ft_strdupline(game->file.full_file_one_line, game, color_start, *i);
	(*i) = (*i) + 1;
	return(path);
}

int	find_color(t_game *game, int *i)
{
	if (game->file.full_file_one_line[*i] == 'F')
	{
		game->file.F += 1;
		game->file.F_path = recover_color(game, &game->file, i);
		return(1);
	}
	else if (game->file.full_file_one_line[*i] == 'C')
	{
		game->file.C += 1;
		game->file.C_path = recover_color(game, &game->file, i);
		printf("[DEBUG] i value is: %d\n", (*i)); //debug
		return(1);
	}
	return(0);
}
