#include "cub3d.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*destination;
	char	*source;

	if (dst == NULL && src == NULL)
		return (0);
	i = 0;
	destination = (char *)dst;
	source = (char *)src;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup_path(const char *s, t_game *game, int start, int end)
{
	char	*src;
	char	*scopy;
	int		x;

	src = (char *)s;
	scopy = (char *) arena_alloc(game->arena,
			((end - start) + 1) * sizeof(char));
	x = 0;
	while (start < end)
	{
		if (src[start] == ' ')
			simple_exit("Error\nError in path\n", game);
		scopy[x] = src[start];
		x++;
		start++;
	}
	scopy[x] = '\0';
	return (scopy);
}

char	*ft_strdup_color(const char *s, t_game *game, int start, int end)
{
	char	*src;
	char	*scopy;
	int		x;

	src = (char *)s;
	scopy = (char *) arena_alloc(game->arena,
			((end - start) + 1) * sizeof(char));
	x = 0;
	while (start < end)
	{
		while (src[start] == ' ')
			start++;
		scopy[x] = src[start];
		x++;
		start++;
	}
	scopy[x] = '\0';
	return (scopy);
}

int	ft_simple_atoi(const char *str, t_game *game)
{
	int	result;
	int	i;
	int	x;

	result = 0;
	i = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] < '0' || str[x] > '9')
			simple_exit("Error\nInvalid color\n", game);
		x++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i = i + 1;
	}
	return (result);
}
