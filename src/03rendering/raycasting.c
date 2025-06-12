/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:52:05 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 09:52:05 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_wall_bounds(t_ray *ray, int *draw_start, int *draw_end)
{
	int	line_height;

	line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	*draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (*draw_end >= WINDOW_HEIGHT)
		*draw_end = WINDOW_HEIGHT - 1;
}

static int	calculate_texture_x(t_game *game, t_ray *ray, mlx_image_t *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_line(t_game *game, int x, t_ray *ray)
{
	int			draw_bounds[2];
	int			tex_coords[2];
	int			line_height;
	int			y;
	mlx_image_t	*tex;

	calculate_wall_bounds(ray, &draw_bounds[0], &draw_bounds[1]);
	tex = get_wall_texture(game, ray);
	tex_coords[0] = calculate_texture_x(game, ray, tex);
	line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	y = draw_bounds[0];
	while (y <= draw_bounds[1])
	{
		draw_bounds[0] = y * 256 - WINDOW_HEIGHT * 128 + line_height * 128;
		tex_coords[1] = ((draw_bounds[0] * tex->height) / line_height) / 256;
		draw_bounds[0] = get_texture_pixel(tex, tex_coords[0], tex_coords[1]);
		mlx_put_pixel(game->image, x, y, draw_bounds[0]);
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
int longest_column_bonus(t_game *game) // bonus
{
	int	y;
	int longest;
	int	temp;

	y = 1;
	longest = ft_strlen(game->file.map_matrix[0]);
	while(game->file.map_matrix[y])
	{
		temp = ft_strlen(game->file.map_matrix[y]);
		if (temp > longest)
			longest = temp;
		y++;
	}
	return (longest);
}
void	rendering(t_game *game)
{
	int	longest;//bonus
	static bool printed;// bonus

	longest = longest_column_bonus(game);// bonus
	render_background(game);
	raycast(game);
	if(game->file.total_rows < WINDOW_HEIGHT / 20 && longest < WINDOW_WIDTH / 20) // bonus
		draw_mini_map(game);// bonus
	else if ((game->file.total_rows >= WINDOW_HEIGHT / 20 || longest >= WINDOW_WIDTH / 20))                 //bonus
	{
			if(!printed)
			{
				ft_putstr_fd("Error\nMinimap maxsize 1/20\n",2);//bonus
				printed = true;
			}
	}
}
