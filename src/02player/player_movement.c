#include "cub3d.h"

void close_window(void *param)
{
    t_game *game = (t_game *)param;
    mlx_close_window(game->mlx);
}

void init_player_position(t_game *game)
{
    int y;
    int x;
    char c;

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

                if (c == 'E')
                    game->player_angle = 0;           // Est
                else if (c == 'W')
                    game->player_angle = M_PI;        // Ovest
                else if (c == 'S')
                    game->player_angle = M_PI/2;      // Sud
                else if (c == 'N')
                    game->player_angle = (M_PI * 3)/2; // Nord
                game->file.map_matrix[y][x] = '0';
                return;
            }
            x++;
        }
        y++;
    }
}
static bool is_walkable(t_game *game, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;

    if (map_x < 0 || map_y < 0 || map_y >= game->file.total_rows)
        return false;
    if (!game->file.map_matrix[map_y] || map_x >= ft_strlen(game->file.map_matrix[map_y]))
        return false;
    return (game->file.map_matrix[map_y][map_x] != '1');
}

static void move_player(t_game *game, double direction)
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

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    
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
			rotate_player(game, 1.0);
        else if (keydata.key == MLX_KEY_D)
			rotate_player(game, -1.0);

		rendering(game);
    }
}
