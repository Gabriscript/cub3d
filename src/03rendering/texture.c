/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:52:11 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 09:52:11 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*load_single_texture(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putstr_fd((char *)path, 2);
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

int	load_textures(t_game *game)
{
	game->north_img = load_single_texture(game->mlx, game->file.no_path);
	if (!game->north_img)
		return (FAILURE);
	game->south_img = load_single_texture(game->mlx, game->file.so_path);
	if (!game->south_img)
	{
		free_textures(game);
		return (FAILURE);
	}
	game->east_img = load_single_texture(game->mlx, game->file.ea_path);
	if (!game->east_img)
	{
		free_textures(game);
		return (FAILURE);
	}
	game->west_img = load_single_texture(game->mlx, game->file.we_path);
	if (!game->west_img)
	{
		free_textures(game);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	free_textures(t_game *game)
{
	if (game->north_img)
	{
		mlx_delete_image(game->mlx, game->north_img);
		game->north_img = NULL;
	}
	if (game->south_img)
	{
		mlx_delete_image(game->mlx, game->south_img);
		game->south_img = NULL;
	}
	if (game->east_img)
	{
		mlx_delete_image(game->mlx, game->east_img);
		game->east_img = NULL;
	}
	if (game->west_img)
	{
		mlx_delete_image(game->mlx, game->west_img);
		game->west_img = NULL;
	}
}

int	get_texture_pixel(mlx_image_t *texture, int x, int y)
{
	unsigned char	*pixel;

	if (!texture || x < 0 || y < 0 || x >= (int)texture->width
		|| y >= (int)texture->height)
		return (0);
	pixel = &texture->pixels[(y * texture->width + x) * 4];
	return (create_rgba(pixel[0], pixel[1], pixel[2], pixel[3]));
}
