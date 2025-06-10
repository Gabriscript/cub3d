#ifndef ARENA_H
# define ARENA_H
# define ARENA_SIZE (10 * 1024 * 1024)

# include <stdlib.h>

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
