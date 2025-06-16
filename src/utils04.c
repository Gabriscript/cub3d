/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils04.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:08:44 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/16 14:08:48 by cborrome         ###   ########.fr       */
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
