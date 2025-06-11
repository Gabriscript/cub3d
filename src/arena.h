#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>

# define ARENA_SIZE 10485760

typedef struct s_arena
{
	char	*memory;
	size_t	used;
	size_t	capacity;
}		t_arena;

t_arena	*arena_create(size_t size);
void	*arena_alloc(t_arena *arena, size_t size);
void	arena_destroy(t_arena *arena);

#endif
