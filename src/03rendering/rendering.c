/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:52:08 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 09:52:08 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	render_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				mlx_put_pixel(game->image, x, y, create_rgba(game->ceiling[0],
						game->ceiling[1], game->ceiling[2], 255));
			else
				mlx_put_pixel(game->image, x, y, create_rgba(game->floor[0],
						game->floor[1], game->floor[2], 255));
			x++;
		}
		y++;
	}
}

void	update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	rendering(game);
}

static int	check_init(t_game *game)
{
	if (load_textures(game) == FAILURE)
	{
		ft_putstr_fd("Error\nFailed to load textures\n", 2);
		mlx_terminate(game->mlx);
		return (FAILURE);
	}
	game->image = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->image)
	{
		ft_putstr_fd("Error\nFailed to create image\n", 2);
		free_textures(game);
		mlx_terminate(game->mlx);
		return (FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		ft_putstr_fd("Error\nFailed to put image to window\n", 2);
		mlx_delete_image(game->mlx, game->image);
		free_textures(game);
		mlx_terminate(game->mlx);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		return (FAILURE);
	}
	if (check_init(game) == FAILURE)
		return (FAILURE);
	init_player_position(game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_close_hook(game->mlx, close_window, game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	mlx_delete_image(game->mlx, game->image);
	free_textures(game);
	mlx_terminate(game->mlx);
	return (SUCCESS);
}
