#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include "arena.h"

# define SUCCESS 0
# define FAILURE 1

typedef struct s_game
{
	char	**map;
	int		map_heigth;
	int		end_of_map;
	char	**file;
	t_arena *arena;
}	t_game;



int		ft_strlen(char *str);
int		ft_strcmp(const char *main, const char *compared);
void	ft_putstr_fd(char *str, int fd);
bool	is_valid_file(char *file, bool cub);
int		ft_isspace(char c);


#endif