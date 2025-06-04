#include "cub3d.h"
#include "get_next_line_bonus.h"

// static bool is_component(char c)
// {
// 	return (c == '0' || c == '1' || c == 'E'
// 			|| c == 'W'  || c == 'S' || c == 'N');
// }
// static int component_index(char c)
// {
// 	if (c == '0')
// 		return (0);
// 	if (c == '1')
// 		return (1);
// 	if (c == 'S')
// 		return (2);
// 	if (c == 'E')
// 		return (3);
// 	if (c == 'W')
// 		return (4);
// 	if (c == 'N')
// 		return (5);
// 	return (-1);
// }

// static bool	count_components(t_game *game, int components[6])
// {
// 	int	x;
// 	int	y;
// 	int	i;

// 	y = 0;
// 	while (y < game->height)
// 	{
// 		x = 0;
// 		while (game->map[y][x])
// 		{
// 			if (is_component(game->map[y][x]))
// 			{
// 				i = component_index(game->map[y][x]);
// 				if (i != -1)
// 				{
// 					components[i]++;
// 					if (i >= 2 && components[i] > 1)
// 						return (false);
// 				}
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (true);
// }
// bool	map_has_all_component(t_game *game)
// {
// 	int	components[6] = {0};
// 	int	count;

// 	if (!count_components(game, components))
// 		return (false);
// 	if (components[0] < 1 || components[1] < 1)
// 		return (false);//mappa non valida
// 	count = components[2] + components[3] + components[4] + components[5];
// 	if (count != 1)
// 		return (false);//troppi players
// 	return (true);
// }

static void	total_file_len_calculation(int fd, t_game *game, t_file *file)
{
	char	*line;
	int		char_in_line;

	line = get_next_line(fd, game);
	char_in_line = 0;
	// if (line == NULL) //controllo necessario??? non ho malloc. forse un messaggio di errore?
	
	while (line != NULL)
	{
		char_in_line = ft_strlen_gnl(line);
		// free(line);
		file->total_file_len = file->total_file_len + char_in_line;
		line = get_next_line(fd, game);

	}
}

void	filling_line(char *map_name, t_game *game)
{
	int		fd;
	ssize_t	bytes_read;

	fd = open(map_name, O_RDONLY);
	bytes_read = read(fd, game->file.full_file_one_line, \
						game->file.total_file_len);
	if (bytes_read == -1)
	{
		close(fd);
		ft_putstr_fd("Error\nError on reading the map\n", 2);
		simple_exit(game);
		exit(EXIT_FAILURE);
	}
	game->file.full_file_one_line[game->file.total_file_len] = '\0';
	close(fd);
}

static void	ft_cub_file_check(char *map_name, t_game *game)
{
	int	fd;
	
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		{
		ft_putstr_fd("Error\nError on opening the map\n", 2);
		simple_exit(game);
		exit (EXIT_FAILURE);
		}
	total_file_len_calculation(fd, game, &game->file);
	close(fd);
	game->file.full_file_one_line = \
			arena_alloc(game->arena, game->file.total_file_len + 1);
	filling_line(map_name, game);
}

void	player_start_position_condition_check(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'N')
			game->file.start_position++;
		if (line[i] == 'S')
			game->file.start_position++;
		if (line[i] == 'W')
			game->file.start_position++;
		if (line[i] == 'E')
			game->file.start_position++;
		i++;
	}
	if (game->file.start_position != 1)
	{
		ft_putstr_fd("Error\nNot a proper map\n", 2);
		simple_exit(game);
		exit (EXIT_FAILURE);
	}
}

void	ft_map_validation(char *argv, t_game *game)
{
	ft_cub_file_check(argv, game);
	//dividiamo la mappa dagli altri dati
	//scorro la full_file_one_line e controllo i 6 dati iniziali
	divede_cub_file(game);

	// map_has_all_component()
	player_start_position_condition_check(game->file.full_map, game);
	fill_map_matrix(game);
	
}
