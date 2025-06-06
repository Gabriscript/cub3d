#include "cub3d.h"

void	argc_check(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		exit (EXIT_FAILURE);
	}
}

void	init_structs(t_game *game)
{
	game->file.full_file_one_line = NULL;
	game->file.full_map = NULL;
	game->file.full_map_zero_check = NULL;
	game->file.total_file_len = 0;
	game->file.total_rows = 0;//
	game->file.start_position = 0;
	game->file.map_matrix = NULL;
	game->file.map_matrix_zero_check = NULL;
	game->file.no = 0;
	game->file.so = 0;
	game->file.we = 0;
	game->file.ea = 0;
	game->file.f = 0;
	game->file.c = 0;
	game->file.no_path = NULL;
	game->file.so_path = NULL;
	game->file.we_path = NULL;
	game->file.ea_path = NULL;
	game->file.f_path = NULL;
	game->file.c_path = NULL;
	game->file.f_r = 0;
	game->file.f_g = 0;
	game->file.f_b = 0;
	game->file.c_r = 0;
	game->file.c_g = 0;
	game->file.c_b = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	argc_check(argc);
	ft_map_name(argv[1]);
	game.arena = arena_create(ARENA_SIZE);
	if (!game.arena)
	{
		// free(game);
		return (FAILURE);
	}
	// init_all(game); // da costruire
	init_structs(&game);
	ft_map_validation(argv[1], &game);

	// graphic_initialisation(game);

	if (init_mlx_window(&game) == FAILURE)
	{
		arena_destroy(game.arena);
		return (FAILURE);
	}
	arena_destroy(game.arena);
	return (SUCCESS);
}
