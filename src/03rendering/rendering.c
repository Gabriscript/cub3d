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
				mlx_put_pixel(game->image, x, y, create_rgba( game->ceiling[0],255,
					game->ceiling[2], 255));
			else
				mlx_put_pixel(game->image, x, y, create_rgba( game->floor[0],
					game->floor[1], game->floor[2], 255));
			x++;
		}
		y++;
	}
}

int	rendering(t_game *game)
{
	render_background(game);
	draw_mini_map(game);
	//raycast();
	return 1;

}


int init_mlx_window(t_game *game)
{
    // Inizializza MLX
    game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
    if (!game->mlx)
    {
        ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
        return (FAILURE);
    }
    game->image = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!game->image)
    {
        ft_putstr_fd("Error\nFailed to create image\n", 2);
        mlx_terminate(game->mlx);
        return (FAILURE);
    }
    // render
    if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
    {
		ft_putstr_fd("Error\nFailed to put image to window\n", 2);
        mlx_delete_image(game->mlx, game->image);
        mlx_terminate(game->mlx);
        return (FAILURE);
    }
	rendering(game);
    mlx_close_hook(game->mlx, close_window, game->mlx);
    mlx_key_hook(game->mlx, key_hook,game->mlx);
    mlx_loop(game->mlx);
    mlx_delete_image(game->mlx, game->image);
    mlx_terminate(game->mlx);
    return (SUCCESS);
}
