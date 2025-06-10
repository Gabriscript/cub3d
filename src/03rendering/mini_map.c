#include "cub3d.h"

static void draw_piece(t_game *game, int y, int x, int size, int color)
{
	int i = 0;
    int j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i < WINDOW_WIDTH && y + j < WINDOW_HEIGHT &&
				x + i >= 0 && y + j >= 0)
				mlx_put_pixel(game->image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static void draw_player(t_game *game)
{
	int player_x = MINI_OFFSET + (int)(game->player_x * MINI_TILE_SIZE);
	int player_y = MINI_OFFSET + (int)(game->player_y * MINI_TILE_SIZE);
	draw_piece(game, player_y, player_x, PLAYER_SIZE, create_rgba(0, 255, 0, 255));


	int i = 1;
	while (i <= 4)
	{
		int dot_x = player_x + (int)(cos(game->player_angle) * i * 2 );
		int dot_y = player_y + (int)(sin(game->player_angle) * i * 2);
		draw_piece(game, dot_y, dot_x, 2, create_rgba(0, 255, 0, 255));
		i++;
	}
}



void draw_mini_map(t_game *game)
{
	int y = 0, x, color, screen_x, screen_y;
	while (y < game->file.total_rows)
	{
		x = 0;
		while (game->file.map_matrix[y] && game->file.map_matrix[y][x])
		{
			screen_x = MINI_OFFSET + x * MINI_TILE_SIZE;
			screen_y = MINI_OFFSET + y * MINI_TILE_SIZE;
			if (game->file.map_matrix[y][x] == '1')
				color = create_rgba(100, 100, 100, 255);
			else if (game->file.map_matrix[y][x] == '0')
				color = create_rgba(255, 255, 255, 255);
			else
				color = create_rgba(0, 0, 0, 0);
			draw_piece(game, screen_y, screen_x, MINI_TILE_SIZE, color);
			x++;
		}
		y++;
	}
	draw_player(game);
}