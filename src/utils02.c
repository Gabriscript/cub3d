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

char	*ft_strndup(const char *s, t_game *game, int start, int end)
{
	char	*src;
	char	*scopy;
	int		x;

	src = (char *)s;
	scopy = (char *) arena_alloc(game->arena, (ft_strlen(end - start) + 1) * sizeof(char));
	// if (scopy == NULL)
	// 	return (NULL);
	x = start;
	while (x < end)
	{
		scopy[x] = src[x];
		x++;
	}
	scopy[x] = '\0';
	return (scopy);
}
