/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:22:08 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/16 10:45:37 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	longest_column_bonus(t_game *game)
{
	int	y;
	int	longest;
	int	temp;

	y = 1;
	longest = ft_strlen(game->file.map_matrix[0]);
	while (game->file.map_matrix[y])
	{
		temp = ft_strlen(game->file.map_matrix[y]);
		if (temp > longest)
			longest = temp;
		y++;
	}
	return (longest);
}

void	rendering(t_game *game)
{
	int			longest;
	static bool	printed;

	longest = longest_column_bonus(game);
	render_background(game);
	raycast(game);
	if (game->file.total_rows < WINDOW_HEIGHT / 20
		&& longest < WINDOW_WIDTH / 20)
		draw_mini_map(game);
	else if ((game->file.total_rows >= WINDOW_HEIGHT / 20
			|| longest >= WINDOW_WIDTH / 20))
	{
		if (!printed)
		{
			ft_putstr_fd("Error\nMinimap maxsize 1/20\n", 2);
			printed = true;
		}
	}
}
