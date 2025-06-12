/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:52:00 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 09:52:00 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_piece(t_game *game, int y, int x, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (size == PLAYER_SIZE)
		game->color = create_rgba(0, 255, 0, 255);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i < WINDOW_WIDTH && y + j < WINDOW_HEIGHT
				&& x + i >= 0 && y + j >= 0)
				mlx_put_pixel(game->image, x + i, y + j, game->color);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_game *game)
{
	int	player_x;
	int	player_y;
	int	i;
	int	dot_x;
	int	dot_y;

	player_x = MINI_OFFSET + (int)(game->player_x * MINI_TILE_SIZE);
	player_y = MINI_OFFSET + (int)(game->player_y * MINI_TILE_SIZE);
	draw_piece(game, player_y, player_x, PLAYER_SIZE);
	i = 1;
	while (i <= 4)
	{
		dot_x = player_x + (int)(cos(game->player_angle) * i * 2);
		dot_y = player_y + (int)(sin(game->player_angle) * i * 2);
		draw_piece(game, dot_y, dot_x, 2);
		i++;
	}
}

void	draw_mini_map(t_game *game)
{
	int	y;
	int	x;
	int	screen_x;
	int	screen_y;

	y = 0;
	while (y < game->file.total_rows)
	{
		x = 0;
		while (game->file.map_matrix[y] && game->file.map_matrix[y][x])
		{
			screen_x = MINI_OFFSET + x * MINI_TILE_SIZE;
			screen_y = MINI_OFFSET + y * MINI_TILE_SIZE;
			if (game->file.map_matrix[y][x] == '1')
				game->color = create_rgba(100, 100, 100, 255);
			else if (game->file.map_matrix[y][x] == '0')
				game->color = create_rgba(255, 255, 255, 255);
			else
				game->color = create_rgba(0, 0, 0, 0);
			draw_piece(game, screen_y, screen_x, MINI_TILE_SIZE);
			x++;
		}
		y++;
	}
	draw_player(game);
}
