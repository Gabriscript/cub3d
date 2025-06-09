#include "cub3d.h"

static void	draw_piece(t_game *game, int y, int x, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->mini_size)
	{
		j = 0;
		while (j < game->mini_size)
		{
			if (x + i < WINDOW_WIDTH && y + j < WINDOW_HEIGHT && 
				x + i >= 0 && y + j >= 0)
				mlx_put_pixel(game->image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
static void	draw_player(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = MINI_OFFSET + (int)(game->player_x * MINI_MAP);
	player_y = MINI_OFFSET + (int)(game->player_y * MINI_MAP);
	game->mini_size = MINI_MAP / 10;
	draw_piece(game, player_y, player_x, create_rgba(0, 255, 0, 255));
}
void draw_mini_map(t_game *game)
{
    int y;
    int x;
    int color;
    int screen_x;
    int screen_y;
    
    y = 0;
    while (y < game->file.total_rows)
    {
        x = 0;
        while (game->file.map_matrix[y] && game->file.map_matrix[y][x])
        {
            screen_x = MINI_OFFSET + x * MINI_MAP;
            screen_y = MINI_OFFSET + y * MINI_MAP;
            if (game->file.map_matrix[y][x] == '1')
                color = create_rgba(100, 100, 100, 255);
            else if (game->file.map_matrix[y][x] == '0')
                color = create_rgba(255, 255, 255, 255);
            else 
                color = create_rgba(0, 255, 255, 255);
            game->mini_size = MINI_MAP;
            draw_piece(game, screen_y, screen_x, color);
            x++;
        }
        y++;
    }
    draw_player(game);    
}
