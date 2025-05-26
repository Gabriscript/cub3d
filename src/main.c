#include "cub3d.h"

void	arena_test(t_arena *arena)
{
	char *s1 = arena_strdup(arena, "Hello");
	char *s2 = arena_strjoin(arena, s1, " world!");

	write(1, s2, strlen(s2));
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
	write(1, "[DEBUG] Arena created and ready!\n", 34);
	arena_test(game->arena); //DEBUG-TEST


	// calling any usefull function as game start!!!

	arena_destroy(game->arena);
	free(game);
	return (SUCCESS);
}