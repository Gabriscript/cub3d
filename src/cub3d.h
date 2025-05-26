#ifndef CUB3D_H
#define CUB3D_H

# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>

#include "arena.h"

# define SUCCESS 0
# define FAILURE 1

typedef struct s_game
{
	t_arena *arena;
}	t_game;



int		ft_strlen(char *str);

#endif