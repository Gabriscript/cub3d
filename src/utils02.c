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

char	*ft_strdupline(const char *s, t_game *game, int start, int end)
{
	char	*src;
	char	*scopy;
	int		x;
	// printf("[DEBUG] in utils02.c S: %s\n", s);//debug

printf("[DEBUG] in utils02.c START: %d\n", start);//debug
printf("[DEBUG] in utils02.c END: %d\n", end);//debug	
	src = (char *)s;
	scopy = (char *) arena_alloc(game->arena, ((end - start) + 1) * sizeof(char));
	// if (scopy == NULL)
	// 	return (NULL);
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
	printf("[DEBUG] in utils02.c SCOPY: %s\n", scopy);//debug
	return (scopy);
}
