/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:52:34 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 09:52:35 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	argc_check(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		exit (EXIT_FAILURE);
	}
}

static void	path_rgb_init(t_game *game)
{
	game->file.no_path = NULL;
	game->file.so_path = NULL;
	game->file.we_path = NULL;
	game->file.ea_path = NULL;
	game->file.f_path = NULL;
	game->file.c_path = NULL;
	game->floor[0] = 0;
	game->floor[1] = 0;
	game->floor[2] = 0;
	game->ceiling[0] = 0;
	game->ceiling[1] = 0;
	game->ceiling[2] = 0;
}

static void	init_structs(t_game *game)
{
	game->file.full_file_one_line = NULL;
	game->file.full_map = NULL;
	game->file.full_map_flood_fill = NULL;
	game->file.total_file_len = 0;
	game->file.total_rows = 0;
	game->file.start_position = 0;
	game->file.start_position_row = 0;
	game->file.start_position_col = 0;
	game->file.map_matrix = NULL;
	game->file.map_matrix_flood_fill = NULL;
	game->file.no = 0;
	game->file.so = 0;
	game->file.we = 0;
	game->file.ea = 0;
	game->file.f = 0;
	game->file.c = 0;
	path_rgb_init(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	argc_check(argc);
	ft_map_name(argv[1]);
	game.arena = arena_create(ARENA_SIZE);
	if (!game.arena)
		return (FAILURE);
	init_structs(&game);
	ft_map_validation(argv[1], &game);
	if (init_mlx_window(&game) == FAILURE)
	{
		arena_destroy(game.arena);
		return (FAILURE);
	}
	arena_destroy(game.arena);
	return (SUCCESS);
}
