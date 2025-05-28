#include "cub3d.h"

// void	arena_test(t_arena *arena)
// {
// 	char *s1 = arena_strdup(arena, "Hello");
// 	char *s2 = arena_strjoin(arena, s1, " world!");

// 	ft_putstr_fd( s2, 1);
// 	write(1, "\n", 1);
// }

// int	main (int argc, char **argv)
// {
// 	t_game	*game;

// 	game = malloc(sizeof(t_game));
// 	if (!game)
// 		return (FAILURE);
// 	game->arena = arena_create(ARENA_SIZE);
// 	if (!game->arena)
// 	{
// 		free(game);
// 		return (FAILURE);
// 	}

// 	ft_putstr_fd("[DEBUG] Arena created and ready!\n", 1);
// 	arena_test(game->arena); //DEBUG-TEST

// 	arena_destroy(game->arena);
// 	free(game);
// 	return (SUCCESS);
// }


int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	ft_map_name(argv[1]);

	game = malloc(sizeof(t_game));
	if (!game)
		return (FAILURE);
	game->arena = arena_create(ARENA_SIZE);
	if (!game->arena)
	{
		free(game);
		return (FAILURE);
	}

	if (!is_valid_file(argv[1], true))
	{
		simple_exit(game);
		return (1);
	}
	if (init_mlx_window(game) == FAILURE)
	{
		simple_exit(game);
		return (FAILURE);
	}
	// calling any usefull function as game start!!!

	simple_exit(game);
	return (SUCCESS);
}
