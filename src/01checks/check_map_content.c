#include "cub3d.h"

static bool is_component(char c)
{
	return (c == '0' || c == '1' || c == 'E'
			|| c == 'W'  || c == 'S' || c == 'N');
}
static int component_index(char c)
{
	if (c == '0')
		return (0);
	if (c == '1')
		return (1);
	if (c == 'S')
		return (2);
	if (c == 'E')
		return (3);
	if (c == 'W')
		return (4);
	if (c == 'N')
		return (5);
	return (-1);
}

static bool	count_components(t_game *game, int components[6])
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (is_component(game->map[y][x]))
			{
				i = component_index(game->map[y][x]);
				if (i != -1)
				{
					components[i]++;
					if (i >= 2 && components[i] > 1)
						return (false);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}
bool	map_has_all_component(t_game *game)
{
	int	components[6] = {0};
	int	count;

	if (!count_components(game, components))
		return (false);
	if (components[0] < 1 || components[1] < 1)
		return (false);
	count = components[2] + components[3] + components[4] + components[5];
	if (count != 1)
		return (false);
	return (true);
}

