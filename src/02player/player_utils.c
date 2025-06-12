/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:51:54 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 14:12:28 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_walkable(t_game *game, double x, double y)
{
	int		map_y_l;
	int		map_y_r;
	int		map_x_l;
	int		map_x_r;
	double	radius;

	radius = 0.7;
	map_y_l = (int)(y + radius);
	map_y_r = (int)(y - radius);
	map_x_l = (x + radius);
	map_x_r = (x - radius);
	if (map_x_l < 0 || map_y_l < 0 || map_y_l >= game->file.total_rows)
		return (false);
	if (!game->file.map_matrix[map_y_r]
		|| map_x_r >= ft_strlen(game->file.map_matrix[map_y_r]))
		return (false);
	if (game->file.map_matrix[map_y_r][map_x_r] == '1'
		|| game->file.map_matrix[map_y_l][map_x_l] == '1'
		|| game->file.map_matrix[map_y_l][map_x_r] == '1'
		|| game->file.map_matrix[map_y_l][map_x_r] == '1')
		return (false);
	return (true);
}

void	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_close_window(game->mlx);
}

static void	set_player_angle(char c, t_game *game)
{
	if (c == 'E')
		game->player_angle = 0;
	else if (c == 'W')
		game->player_angle = M_PI;
	else if (c == 'S')
		game->player_angle = M_PI / 2;
	else if (c == 'N')
		game->player_angle = (M_PI * 3) / 2;
}

void	init_player_position(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->file.total_rows && game->file.map_matrix[y])
	{
		x = 0;
		while (game->file.map_matrix[y][x])
		{
			c = game->file.map_matrix[y][x];
			if (c == 'E' || c == 'W' || c == 'S' || c == 'N')
			{
				game->player_x = x + 0.5;
				game->player_y = y + 0.5;
				set_player_angle(c, game);
				game->file.map_matrix[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
