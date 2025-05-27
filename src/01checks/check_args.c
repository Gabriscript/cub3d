#include "cub3d.h"

bool map_is_at_end(t_game *game)
{
	int	y;
	int	x;
	int i;

	y = game->end_of_map;
	while (game->file[y])
	{
		x = 0;
		while(game->file[y][x])
		{
			i = game->file[y][x];
			if (!ft_isspace(i) || i != '\n' )
				return (false);
			x++;
		}
		y++;
	}
	return (true);

}