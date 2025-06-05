#include "cub3d.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void render_background(t_game *game)
{
    int x, y;

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


void init_test_map(t_game *game)
{
    // Crea una mappa di test 10x10
    game->height = 10;
    game->map = (char **)arena_alloc(game->arena, 11 * sizeof(char *));
    
    // Mappa di test con muri perimetrali e un giocatore al centro
    char *test_map[] = {
        "1111111111",
        "1000000001", 
        "1000100001",
        "1000000001",
        "1000N00001",  // N = giocatore rivolto a Nord
        "1000000001",
        "1000100001",
        "1000000001",
        "1000000001",
        "1111111111",
        NULL
    };
    
    for (int i = 0; i < 10; i++)
    {
        int len = ft_strlen(test_map[i]);
        game->map[i] = (char *)arena_alloc(game->arena, (len + 1) * sizeof(char));
        ft_memcpy(game->map[i], test_map[i], len);
        game->map[i][len] = '\0';
    }
    game->map[10] = NULL;
    
    // Inizializza colori di default
    game->ceiling[0] = 135; // Sky blue
    game->ceiling[1] = 206;
    game->ceiling[2] = 235;
    
    game->floor[0] = 139;   // Brown
    game->floor[1] = 69;
    game->floor[2] = 19;
    
    // Inizializza posizione giocatore
    init_player_position(game);
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
    mlx_close_hook(game->mlx, close_window, game);
    mlx_key_hook(game->mlx, key_hook,game);
    mlx_loop(game->mlx);
    mlx_delete_image(game->mlx, game->image);
    mlx_terminate(game->mlx);
    return (SUCCESS);
}
