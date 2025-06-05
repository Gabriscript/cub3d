#include "cub3d.h"

mlx_image_t* load_single_texture(mlx_t* mlx, const char* path)
{
    mlx_texture_t* texture;
    mlx_image_t* image;
    
    texture = mlx_load_png(path);
    if (!texture)
    {
        ft_putstr_fd("Error\nFailed to load texture: ", 2);
        ft_putstr_fd((char*)path, 2);
        ft_putstr_fd("\n", 2);
        return (NULL);
    }
    image = mlx_texture_to_image(mlx, texture);
    if (!image)
    {
        ft_putstr_fd("Error\nFailed to convert texture to image\n", 2);
        mlx_delete_texture(texture);
        return (NULL);
    }
    mlx_delete_texture(texture);
    return (image);
}


int load_textures(t_game *game)
{

    game->north_img = load_single_texture(game->mlx, "../../FPStextures/FPS64x/Texture0.png");
    if (!game->north_img)
        return (FAILURE);
        
    game->south_img = load_single_texture(game->mlx, "../../FPStextures/FPS64x/Texture1.png");
    if (!game->south_img)
        return (FAILURE);
        
    game->east_img = load_single_texture(game->mlx, "../../FPStextures/FPS64x/Texture2.png");
    if (!game->east_img)
        return (FAILURE);
        
    game->west_img = load_single_texture(game->mlx, "../../FPStextures/FPS64x/Texture3.png");
    if (!game->west_img)
        return (FAILURE);
    
    return (SUCCESS);
}

void free_textures(t_game *game)
{
    if (game->north_img)
        mlx_delete_image(game->mlx, game->north_img);
    if (game->south_img)
        mlx_delete_image(game->mlx, game->south_img);
    if (game->east_img)
        mlx_delete_image(game->mlx, game->east_img);
    if (game->west_img)
        mlx_delete_image(game->mlx, game->west_img);
}
