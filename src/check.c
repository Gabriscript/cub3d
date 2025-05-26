#include "cub3d.h"

static bool	is_cub_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (false);
	return (ft_strcmp(&file[len - 4], ".cub"));
}

static bool	is_png_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (false);
		return (ft_strcmp(&file[len - 4], ".png"));
}
static bool	is_readable_and_exist(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("File does not exist or has not reading permission", 2);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
static bool is_directory(char *file)
{
	int	fd;

	fd = open(file, __O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd("Directory is not a valid file", 2);
		close(fd);
		return (true);
	}	
	close(fd);
	return (false);
}

bool	is_valid_file(char *file, bool cub)
{
	if (is_directory(file))
		return (false);
	if (!is_readable_and_exist(file))
		return (false);
	if (cub && is_cub_file(file))
		return (true);
	if (!cub && is_png_file(file))
		return (true);
}
