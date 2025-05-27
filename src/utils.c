#include "cub3d.h"


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
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

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write (fd, str, ft_strlen(str));
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}