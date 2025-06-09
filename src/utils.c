#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && (s[i] != c))
	{
		i++;
	}
	if (s[i] != c)
		return (NULL);
	else
		return ((char *)s + i);
}

int	ft_strcmp(const char *main, const char *compared)
{
	int	i;

	i = 0;
	while (compared[i] || main[i])
	{
		if (compared[i] != main[i])
			return (main[i] - compared[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n && (s1[x] != '\0' || s2[x] != '\0'))
	{
		if ((unsigned char)s1[x] != (unsigned char)s2[x])
		{
			return ((unsigned char)s1[x] - (unsigned char)s2[x]);
		}
		x++;
	}
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	   ssize_t bytes_written = write(fd, str, ft_strlen(str));
    if (bytes_written == -1)
        perror("write");
}

