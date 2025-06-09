#include "cub3d.h"
void init_ray(t_game *game, t_ray *ray, int x)
{
	double camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;										  // coordinata x nella camera (-1 a 1)
	ray->ray_dir_x = cos(game->player_angle) + sin(game->player_angle) * camera_x * 0.66; // è il piano della camera
	ray->ray_dir_y = sin(game->player_angle) - cos(game->player_angle) * camera_x * 0.66;

	// Quale cella della mappa siamo
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;

	// Lunghezza del raggio dalla posizione attuale al prossimo lato x o y
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		 ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	ray->side = -1;
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

void perform_dda(t_game *game, t_ray *ray)
{
    while (ray->hit == 0)
    {
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
        if (ray->map_x < 0 || ray->map_y < 0 || 
            ray->map_y >= game->file.total_rows ||
            !game->file.map_matrix[ray->map_y] ||
            ray->map_x >= ft_strlen(game->file.map_matrix[ray->map_y]) ||
            game->file.map_matrix[ray->map_y][ray->map_x] == '1')
        {
            ray->hit = 1;
        }
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
	int line_height;
	int draw_start;
	int draw_end;
	int color;
	int y;

	line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);

	// Calcola il punto più alto e più basso da disegnare sullo schermo
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	if (ray->side == 1) // Muro est-ovest (più scuro)
		color = create_rgba(100, 100, 100, 255);
	else // Muro nord-sud (più chiaro)
		color = create_rgba(150, 150, 150, 255);
	y = draw_start;
	while (y <= draw_end)
	{
		mlx_put_pixel(game->image, x, y, color);
		y++;
	}
}


void	raycast(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall_distance(game, &ray);
		draw_wall_line(game, x, &ray);
		x++;
	}
}


int rendering(t_game *game)
{
	render_background(game);
	raycast(game);
	draw_mini_map(game);
	return 1;
}