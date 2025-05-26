#include "cub3d.h"

static bool	is_cub_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	return (file[len - 1] != 'b' || file[len - 2] != 'u' 
		|| file[len - 3] != 'c' || file[len - 4] != '.');
}