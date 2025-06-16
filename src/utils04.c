/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils04.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:08:44 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/16 15:10:34 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*pointer;
	size_t	x;

	if (count == 0 || size == 0)
		return (malloc(1));
	total_size = count * size;
	pointer = (void *)malloc(total_size);
	x = 0;
	if (pointer == NULL)
		return (NULL);
	while (x < total_size)
	{
		pointer[x] = 0;
		x++;
	}
	return (pointer);
}
