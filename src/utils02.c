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
