#include "cub3d.h"

void	recover_path(t_game *game, t_file *file, int *i)
{
	int	path_start;
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
	else
	{
		path_start = *i;
		while(game->file.full_file_one_line[*i] != '\n')
			(*i)++;
		ft_strdupline(game->file.full_file_one_line, game, path_start, *i);
		(*i) = (*i) + 1;
	}
}

static int	find_path_1(t_game *game, int *i)
{
	if (game->file.full_file_one_line[*(i)] == 'N' && \
		game->file.full_file_one_line[*(i) + 1] == 'O')
		{
			game->file.NO += 1;
			recover_path(game, &game->file, i);
			return(1);
		}
	else if (game->file.full_file_one_line[*(i)] == 'S' && \
		game->file.full_file_one_line[*(i) + 1] == 'O')
		{
			game->file.SO += 1;
			recover_path(game, &game->file, i);
			return(1);
		}
	return(0);
}

static int	find_path_2(t_game *game, int *i)
{
	if (game->file.full_file_one_line[*(i)] == 'W' && \
		game->file.full_file_one_line[*(i) + 1] == 'E')
		{
			game->file.WE += 1;
			recover_path(game, &game->file, i);
			return(1);
		}
	else if (game->file.full_file_one_line[*(i)] == 'E' && \
		game->file.full_file_one_line[*(i) + 1] == 'A')
		{
			game->file.EA += 1;
			recover_path(game, &game->file, i);
			return(1);
		}
	return(0);
}
static void	recover_color(t_game *game, t_file *file, int *i)
{
	int	color_start;
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
	else
	{
		color_start = *i;
		while(game->file.full_file_one_line[*i] != '\n')
			(*i)++;
		ft_strdupline(game->file.full_file_one_line, game, color_start, *i);
		(*i) = (*i) + 1;
	}
}

static int	find_color(t_game *game, int *i)
{
	if (game->file.full_file_one_line[*i] == 'F')
	{
		game->file.F += 1;
		recover_color(game, &game->file, i);
		return(1);
	}
	else if (game->file.full_file_one_line[*i] == 'C')
	{
		game->file.C += 1;
		recover_color(game, &game->file, i);
		return(1);
	}
	return(0);
}

void	info_search(t_game *game)
{
	int	i;
printf("[DEBUG] in info_search.c\n");//debug
	i = 0;
	while(game->file.full_file_one_line[i])
	{
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