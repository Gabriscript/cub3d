#include "cub3d.h"

void	simple_exit(char *message, t_game *game)
{
	ft_putstr_fd(message, 2);
	arena_destroy(game->arena);
	exit(EXIT_FAILURE);
}
