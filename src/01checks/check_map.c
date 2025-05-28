#include "cub3d.h"

void	ft_map_name(char *argv)
{
	size_t	len;
	char	*dot;

	len = ft_strlen(argv);
	dot = ft_strchr(argv, '.');
	if (len < 4)
	{
		ft_putstr_fd("Error\nProvide a proper map\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dot == NULL || ft_strncmp(dot, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nProvide a proper map\n", 2);
		exit(EXIT_FAILURE);
	}
}
