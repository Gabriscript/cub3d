#include "cub3d.h"

static bool check_top_bottom_walls(char *row)
{
	int	x;

	x = 0;
	while (row[x] && ft_isspace(row[x]))
		x++;
	if (row[x] && row[x] != '1')
		return (false);
	while (x < ft_strlen(row) - 1)
	{
		if (row[x] != '1' || !ft_isspace(row[x]))
			return (false);
		x++;
	}
	return (true);
}

static bool check_side_walls(char **map, int height)
{
	int	y;
	int	x;
	int	len;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x] && ft_isspace(map[y][x]))
			x++;
		if (map[y][x] && map[y][x] != '1')
			return (false);
		len = ft_strlen(map[y]) - 1;
		while (len >= 0 && ft_isspace(map[y][len]))
			len--;
		if (len >= 0 && map[y][len] != '1')
			return (false);
		y++;
	}
	return (true);
}

bool is_surrounded(char **map, int height)
{
	if (!map || height <= 0)
		return (false);
	if (!check_top_bottom_walls(map[0])
		|| !check_top_bottom_walls(map[height - 1])
		|| !check_side_walls(map, height))
	{
		ft_putstr_fd("Map is not surrounded", 2);
		return (false);
	}
	return (true);
}
