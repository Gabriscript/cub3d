#include "cub3d.h"

void	close_window(void *param)
{
	t_game *game = (t_game *)param;
	mlx_close_window(game->mlx); //seg fault
}
static bool	is_walkable(t_game *game, double x, double y)
{
    int	map_x;
    int	map_y;
    
    map_x = (int)x;
	map_y = (int)y;
    if (map_x < 0 || map_y < 0 || map_y >= game->height)
        return (false);
    if (map_x >= ft_strlen(game->map[map_y]))
        return (false);
    return (game->map[map_y][map_x] != '1');
}
static void	move_player(t_game *game, double direction)
{
    double new_x;
    double new_y;
    
	new_x = game->player_x + cos(game->player_angle) * SPEED * direction;
	new_y = game->player_y + sin(game->player_angle) * SPEED * direction;
    if (is_walkable(game, new_x, game->player_y))
        game->player_x = new_x;
    if (is_walkable(game, game->player_x, new_y))
        game->player_y = new_y;
}
static void rotate_player(t_game *game, double direction)
{
    game->player_angle += ROTATION_SPEED * direction;
    

    if (game->player_angle < 0)
        game->player_angle += 2 * M_PI;
    if (game->player_angle >= 2 * M_PI)
        game->player_angle -= 2 * M_PI;
}
void	key_hook(mlx_key_data_t keydata, void *param)
{
    t_game *game;

	game = (t_game *)param;
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_ESCAPE)
		{
			close_window(game);

		}
        else if (keydata.key == MLX_KEY_W)
            move_player(game, 1.0);
        else if (keydata.key == MLX_KEY_S)
            move_player(game, -1.0);
        else if (keydata.key == MLX_KEY_A)
            rotate_player(game, -1.0);
        else if (keydata.key == MLX_KEY_D)
            rotate_player(game, 1.0); 
    }
}
void	init_player_position(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->map[y][x])
		{
			c = game->map[y][x];
			if (c == 'E' || c == 'W' ||c == 'S' ||c == 'N')
			{
				game->player_x = x;
				game->player_y = y;

				if (c == 'E')
					game->player_angle = 0;
				else if (c == 'W')
					game->player_angle = M_PI;
				else if (c == 'S')
					game->player_angle = M_PI/2;
				else if (c == 'N')
					game->player_angle = (M_PI * 3)/2;
				return ;
			}

			x++;
		}
		y++;
	}

}
