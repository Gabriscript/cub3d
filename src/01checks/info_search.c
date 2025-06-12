/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:51:18 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 10:22:05 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	path_check(char *path_str, t_game *game)
{
	int	path_len;
	int	fd;

	path_len = ft_strlen(path_str);
	if (path_len < 4 || ft_strcmp(path_str + path_len - 4, ".png") != 0)
		simple_exit("Error\nTexture must be .png file\n", game);
	fd = open(path_str, O_RDONLY);
	if (fd == -1)
	{
		simple_exit("Error\nError on opening the picture\n", game);
	}
	close(fd);
}

static void	info_checks(t_game *game)
{
	if (game->file.no != 1 || game->file.so != 1
		|| game->file.we != 1 || game->file.ea != 1)
		simple_exit("Error\nMissing path identifier\n", game);
	if (game->file.f != 1 || game->file.c != 1)
		simple_exit("Error\nMissing color identifier\n", game);
	path_check(game->file.no_path, game);
	path_check(game->file.so_path, game);
	path_check(game->file.we_path, game);
	path_check(game->file.ea_path, game);
	color_check(game);
}

static void	cub_map_part(t_game *game, int *y)
{
	int	map_len;

	map_len = game->file.total_file_len - (*y);
	game->file.full_map = arena_alloc(game->arena, map_len + 1);
	ft_memcpy(game->file.full_map, game->file.full_file_one_line
		+ (*y), map_len);
	game->file.full_map[map_len] = '\0';
	if (ft_strlen(game->file.full_map) < 11)
		simple_exit("Error\nNot a proper map\n", game);
	game->file.full_map_flood_fill = arena_alloc(game->arena, map_len + 1);
	ft_memcpy(game->file.full_map_flood_fill, game->file.full_file_one_line
		+ (*y), map_len);
	game->file.full_map_flood_fill[map_len] = '\0';
}

static void	extra_info_check(char *info_line, int stop, t_game *game)
{
	int	start;

	start = 0;
	while (start < stop)
	{
		if (info_line[start] == '\n' || info_line[start] == ' ')
		{
			start++;
			continue ;
		}
		if (info_path_initial_letter(&start, info_line) == 1)
			continue ;
		if (info_line[start] == 'C' || info_line[start] == 'F')
		{
			start += 1;
			while (info_line[start] == ' ' || info_line[start] != '\n')
				(start)++;
			continue ;
		}
		else
			simple_exit("Error\nInvalid info part\n", game);
	}
}

void	info_search(t_game *game)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (game->file.full_file_one_line[i])
	{
		if (y == 0 && game->file.no == 1 && game->file.so == 1 && game->file.we
			== 1 && game->file.ea == 1 && game->file.f == 1 && game->file.c == 1)
			y = i;
		while (game->file.full_file_one_line[i] == '\n'
			|| game->file.full_file_one_line[i] == ' ')
			i++;
		if (find_path_1(game, &i) == 1)
			continue ;
		else if (find_path_2(game, &i) == 1)
			continue ;
		else if (find_color(game, &i) == 1)
			continue ;
		i++;
	}
	info_checks(game);
	extra_info_check(game->file.full_file_one_line, y, game);
	cub_map_part(game, &y);
}
