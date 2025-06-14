/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:51:44 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 09:51:45 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line_bonus.h"

static void	total_file_len_calculation(int fd, t_game *game, t_file *file)
{
	char	*line;
	int		char_in_line;

	line = get_next_line(fd, game);
	char_in_line = 0;
	if (line == NULL)
		simple_exit("Error\nNULL line\n", game);
	while (line != NULL)
	{
		char_in_line = ft_strlen_gnl(line);
		file->total_file_len = file->total_file_len + char_in_line;
		line = get_next_line(fd, game);
	}
	if (file->total_file_len == 0)
		simple_exit("Error\nEmpty file\n", game);
}

void	filling_line(char *map_name, t_game *game)
{
	int		fd;
	ssize_t	bytes_read;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		simple_exit("Error\nError on opening the map\n", game);
	bytes_read = read(fd, game->file.full_file_one_line,
			game->file.total_file_len);
	if (bytes_read == -1)
	{
		close(fd);
		simple_exit("Error\nError on reading the map\n", game);
	}
	game->file.full_file_one_line[game->file.total_file_len] = '\0';
	close(fd);
}

static void	ft_cub_file_check(char *map_name, t_game *game)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		simple_exit("Error\nError on opening the map\n", game);
	total_file_len_calculation(fd, game, &game->file);
	close(fd);
	game->file.full_file_one_line = arena_alloc(game->arena,
			game->file.total_file_len + 1);
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
		simple_exit("Error\nNot a proper map\n", game);
}

void	ft_map_validation(char *argv, t_game *game)
{
	ft_cub_file_check(argv, game);
	info_search(game);
	player_start_position_condition_check(game->file.full_map, game);
	map_allowed_char_check(game->file.full_map, game);
	map_new_lines_check(game->file.full_map, game);
	game->file.map_matrix = ft_split(game->file.full_map, '\n', game);
	find_player(game);
	map_validation_flood_fill(game, game->file.map_matrix_flood_fill,
		game->file.start_position_row, game->file.start_position_col);
	space_to_wall(game->file.map_matrix);
}
