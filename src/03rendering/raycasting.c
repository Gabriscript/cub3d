#include"cub3d.h"
void init_ray(t_game *game, t_ray *ray, int x)
{
    ray->side = -1;
    // Calcola la direzione del raggio
    double camera_x = 2 * x / (double)WINDOW_WIDTH - 1; // coordinata x nella camera (-1 a 1)
    ray->ray_dir_x = cos(game->player_angle) + sin(game->player_angle) * camera_x * 0.66; // 0.66 è il piano della camera
    ray->ray_dir_y = sin(game->player_angle) - cos(game->player_angle) * camera_x * 0.66;
    
    // Quale cella della mappa siamo
    ray->map_x = (int)game->player_x;
    ray->map_y = (int)game->player_y;
    
    // Lunghezza del raggio dalla posizione attuale al prossimo lato x o y
    ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);
    
    ray->hit = 0; // Il muro è stato colpito?
    
    // Calcola step e side_dist iniziale
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player_x) * ray->delta_dist_x;
    }
    
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player_y) * ray->delta_dist_y;
    }
}

// Esegue l'algoritmo DDA
void perform_dda(t_game *game, t_ray *ray)
{
    while (ray->hit == 0)
    {
        // Salta al prossimo lato della mappa, O in direzione x O in direzione y
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        
        // Controlla se il raggio ha colpito un muro
        if (ray->map_x < 0 || ray->map_x >= ft_strlen(game->map[0]) || 
            ray->map_y < 0 || ray->map_y >= game->height ||
            game->map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

// Calcola la distanza del muro e l'altezza della linea
void calculate_wall_distance(t_game *game, t_ray *ray)
{
    if (!ray->side)
        ray->perp_wall_dist = (ray->map_x - game->player_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - game->player_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

// Disegna una linea verticale per rappresentare il muro
void draw_wall_line(t_game *game, int x, t_ray *ray)
{
    int line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
    
    // Calcola il punto più alto e più basso da disegnare sullo schermo
    int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_start < 0) draw_start = 0;
    int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_end >= WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT - 1;
    
    // Scegli il colore del muro
    int color;
    if (ray->side == 1) // Muro est-ovest (più scuro)
        color = create_rgba(100, 100, 100, 255);
    else // Muro nord-sud (più chiaro)
        color = create_rgba(150, 150, 150, 255);
    
    // Disegna la linea verticale
    for (int y = draw_start; y <= draw_end; y++)
    {
        mlx_put_pixel(game->image, x, y, color);
    }
}

// Funzione principale del raycasting
void raycast(t_game *game)
{
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        t_ray ray;
        
        // Inizializza il raggio
        init_ray(game, &ray, x);
        
        // Esegui DDA
        perform_dda(game, &ray);
        
        // Calcola la distanza
        calculate_wall_distance(game, &ray);
        
        // Disegna la linea del muro
        draw_wall_line(game, x, &ray);
    }
}

// Aggiorna la funzione rendering per includere il raycasting
int rendering(t_game *game)
{
    render_background(game);
    raycast(game);  // Aggiungi il raycasting
    draw_mini_map(game);
    return 1;
}