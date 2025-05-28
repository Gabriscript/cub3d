#include "cub3d.h"

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
    if (x >= image->width || y >= image->height)
        return;
    
    uint8_t* pixel = &image->pixels[(y * image->width + x) * 4];
    pixel[0] = (color >> 24) & 0xFF; // R
    pixel[1] = (color >> 16) & 0xFF; // G
    pixel[2] = (color >> 8) & 0xFF;  // B
    pixel[3] = color & 0xFF;         // A
}

// Funzione per disegnare un rettangolo
void draw_rectangle(mlx_image_t* image, int x, int y, int width, int height, uint32_t color)
{
    for (int i = y; i < y + height && i < (int)image->height; i++)
    {
        for (int j = x; j < x + width && j < (int)image->width; j++)
        {
            put_pixel(image, j, i, color);
        }
    }
}

// Funzione per disegnare una griglia semplice
void draw_simple_scene(mlx_image_t* image)
{
    // Sfondo nero
    for (uint32_t y = 0; y < image->height; y++)
    {
        for (uint32_t x = 0; x < image->width; x++)
        {
            put_pixel(image, x, y, 0x000000FF); // Nero con alpha 255
        }
    }
    
    // Disegna alcuni rettangoli colorati
    draw_rectangle(image, 100, 100, 100, 100, 0xFF0000FF); // Rosso
    draw_rectangle(image, 250, 150, 80, 80, 0x00FF00FF);   // Verde  
    draw_rectangle(image, 400, 200, 120, 60, 0x0000FFFF);  // Blu
    
    // Disegna una griglia semplice
    for (int i = 0; i < WINDOW_WIDTH; i += 50)
    {
        for (int y = 0; y < WINDOW_HEIGHT; y++)
        {
            put_pixel(image, i, y, 0x444444FF); // Grigio scuro
        }
    }
    
    for (int i = 0; i < WINDOW_HEIGHT; i += 50)
    {
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            put_pixel(image, x, i, 0x444444FF); // Grigio scuro
        }
    }
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
    
    // Crea un'immagine
    mlx_image_t* image = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!image)
    {
        ft_putstr_fd("Error\nFailed to create image\n", 2);
        mlx_terminate(game->mlx);
        return (FAILURE);
    }
    
    // Disegna la scena iniziale
    draw_simple_scene(image);
    
    // Mostra l'immagine nella finestra
    if (mlx_image_to_window(game->mlx, image, 0, 0) == -1)
    {
        ft_putstr_fd("Error\nFailed to put image to window\n", 2);
        mlx_delete_image(game->mlx, image);
        mlx_terminate(game->mlx);
        return (FAILURE);
    }
    
    // Imposta i callback
    mlx_close_hook(game->mlx, close_window, game->mlx);
    mlx_key_hook(game->mlx, key_hook,game->mlx);
    
    // Avvia il loop principale
    mlx_loop(game->mlx);
    
    // Cleanup
    mlx_delete_image(game->mlx, image);
    mlx_terminate(game->mlx);
    
    return (SUCCESS);
}