#include "cub3d.h"
// static bool is_component(char c)
// {
// 	return (c == '0' || c == '1' || c == 'E'
// 			|| c == 'W'  || c == 'S' || c == 'N');
// }
// static int component_index(char c)
// {
// 	if (c == '0')
// 		return (0);
// 	if (c == '0')
// 		return (1);
// 	if (c == '0')
// 		return (2);
// 	if (c == '0')
// 		return (3);
// 	if (c == '0')
// 		return (4);
// 	if (c == '0')
// 		return (5);
// 	return (-1);
// }
// static bool array_check(int *array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i] < 6)
// 	{
// 		if (i == 0)
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }
// static bool map_has_all_component(char **map, int height)
// {
// 	int	x;
// 	int	y;
// 	int	i;
// 	int	components[6] = {0};

// 	y = 0;
// 	while (y < height)
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (is_component(map[x][y]))
// 			{
// 				i = component_index(map[x][y]);
// 				if (i != -1)
// 					components[i] = 1;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (array_check(components));
// }
