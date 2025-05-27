#include "cub3d.h"

void	simple_exit(t_game *game)
{
	arena_destroy(game->arena);
	free(game);
}
