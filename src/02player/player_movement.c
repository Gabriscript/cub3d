/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:51:51 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 09:51:51 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_game *game, double direction)
{
	double	new_x;
	double	new_y;

	new_x = game->player_x + cos(game->player_angle) * SPEED * direction;
	new_y = game->player_y + sin(game->player_angle) * SPEED * direction;
	if (is_walkable(game, new_x, game->player_y))
		game->player_x = new_x;
	if (is_walkable(game, game->player_x, new_y))
		game->player_y = new_y;
}

static void	strafe_player(t_game *game, double direction)
{
	double	strafe_angle;
	double	new_x;
	double	new_y;

	strafe_angle = game->player_angle + M_PI / 2;
	new_x = game->player_x + cos(strafe_angle) * SPEED * direction;
	new_y = game->player_y + sin(strafe_angle) * SPEED * direction;
	if (is_walkable(game, new_x, game->player_y))
		game->player_x = new_x;
	if (is_walkable(game, game->player_x, new_y))
		game->player_y = new_y;
}

static void	rotate_player(t_game *game, double direction)
{
	game->player_angle += ROTATION_SPEED * direction;
	if (game->player_angle < 0)
		game->player_angle += 2 * M_PI;
	if (game->player_angle >= 2 * M_PI)
		game->player_angle -= 2 * M_PI;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			close_window(game);
		else if (keydata.key == MLX_KEY_W)
			move_player(game, 1.0);
		else if (keydata.key == MLX_KEY_S)
			move_player(game, -1.0);
		else if (keydata.key == MLX_KEY_A)
			strafe_player(game, 1.0);
		else if (keydata.key == MLX_KEY_D)
			strafe_player(game, -1.0);
		else if (keydata.key == MLX_KEY_LEFT)
			rotate_player(game, 1.0);
		else if (keydata.key == MLX_KEY_RIGHT)
			rotate_player(game, -1.0);
		rendering(game);
	}
}
