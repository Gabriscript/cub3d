#include "cub3d.h"

static void is_directory(char *argv)
{
	int	fd;

	fd = open(argv, __O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd("Error\nDirectory is not a valid file\n", 2);
		close(fd);
		exit(EXIT_FAILURE);
	}	
	close(fd);
}

static void	is_readable_and_exist(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nFile does not exist or has not reading permission\n", 2);
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

/**
 * First: check we have at least 4 char.
 * Second: check we have .cub extension.
 * Third: check if .cub is a directory.
 * Fourth: check if the the file can be read.
 * 
 */
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
	is_directory(argv);
	is_readable_and_exist(argv);
}
