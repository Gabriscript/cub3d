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
	game->file.full_info = NULL;
	game->file.total_file_len = 0;
	game->file.total_rows = 0;
	game->file.start_position = 0;
	game->file.map_matrix = NULL;
	game->file.map_matrix_flood = NULL;
}

int main(int argc, char **argv)
{
    t_game game;

    argc_check(argc);
    ft_map_name(argv[1]);
    
    game.arena = arena_create(ARENA_SIZE);
    if (!game.arena)
        return (FAILURE);
        
    init_structs(&game);
    
    // Per ora usiamo una mappa di test invece del parsing
    init_test_map(&game);
    
    // ft_map_validation(argv[1], &game); // Commenta temporaneamente
    
    if (init_mlx_window(&game) == FAILURE)
    {
        simple_exit(&game);
        return (FAILURE);
    }

    simple_exit(&game);
    return (SUCCESS);
}
