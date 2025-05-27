#include "cub3d.h"

void	arena_test(t_arena *arena)
{
	char *s1 = arena_strdup(arena, "Hello");
	char *s2 = arena_strjoin(arena, s1, " world!");

	ft_putstr_fd( s2, 1);
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	(void)argc;//just for testing
	(void)argv;//just for testing

	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (FAILURE);
	game->arena = arena_create(ARENA_SIZE);
	if (!game->arena)
	{
		free(game);
		return (FAILURE);
	}
	ft_putstr_fd("[DEBUG] Arena created and ready!\n", 1);
	arena_test(game->arena); //DEBUG-TEST


	// calling any usefull function as game start!!!

	arena_destroy(game->arena);
	free(game);
	return (SUCCESS);
}