/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:51:21 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 09:51:22 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*recover_path(t_game *game, t_file *file, int *i)
{
	int		path_start;
	char	*path;

	if (file->no > 1 || file->so > 1 || file->we > 1 || file->ea > 1)
		simple_exit("Error\nToo many path identifier\n", game);
	*i += 2;
	while (game->file.full_file_one_line[*i] == ' ')
		(*i)++;
	if (game->file.full_file_one_line[*i] == '\n')
		simple_exit("Error\nEmpty path\n", game);
	path_start = *i;
	while (game->file.full_file_one_line[*i] != '\n')
		(*i)++;
	path = ft_strdup_path(game->file.full_file_one_line, game, path_start, *i);
	(*i) = (*i) + 1;
	return (path);
}

int	find_path_1(t_game *game, int *i)
{
	if (game->file.full_file_one_line[*(i)] == 'N'
		&& game->file.full_file_one_line[*(i) + 1] == 'O')
	{
		game->file.no += 1;
		game->file.no_path = recover_path(game, &game->file, i);
		return (1);
	}
	else if (game->file.full_file_one_line[*(i)] == 'S'
		&& game->file.full_file_one_line[*(i) + 1] == 'O')
	{
		game->file.so += 1;
		game->file.so_path = recover_path(game, &game->file, i);
		return (1);
	}
	return (0);
}

int	find_path_2(t_game *game, int *i)
{
	if (game->file.full_file_one_line[*(i)] == 'W'
		&& game->file.full_file_one_line[*(i) + 1] == 'E')
	{
		game->file.we += 1;
		game->file.we_path = recover_path(game, &game->file, i);
		return (1);
	}
	else if (game->file.full_file_one_line[*(i)] == 'E'
		&& game->file.full_file_one_line[*(i) + 1] == 'A')
	{
		game->file.ea += 1;
		game->file.ea_path = recover_path(game, &game->file, i);
		return (1);
	}
	return (0);
}

static char	*recover_color(t_game *game, t_file *file, int *i)
{
	int		color_start;
	char	*path;

	if (file->f > 1 || file->c > 1)
		simple_exit("Error\nToo many color identifier\n", game);
	*i += 1;
	while (game->file.full_file_one_line[*i] == ' ')
		(*i)++;
	if (game->file.full_file_one_line[*i] == '\n')
		simple_exit("Error\nEmpty color\n", game);
	color_start = *i;
	while (game->file.full_file_one_line[*i] != '\n')
		(*i)++;
	path = ft_strdup_color(game->file.full_file_one_line,
			game, color_start, *i);
	(*i) = (*i) + 1;
	return (path);
}

int	find_color(t_game *game, int *i)
{
	if (game->file.full_file_one_line[*i] == 'F')
	{
		game->file.f += 1;
		game->file.f_path = recover_color(game, &game->file, i);
		return (1);
	}
	else if (game->file.full_file_one_line[*i] == 'C')
	{
		game->file.c += 1;
		game->file.c_path = recover_color(game, &game->file, i);
		return (1);
	}
	return (0);
}
