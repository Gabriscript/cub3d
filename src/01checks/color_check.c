/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:51:37 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 14:11:05 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	comma_check(char *path, int *x, int *comma_counter, t_game *game)
{
	int	y;

	if (path[*x] == ',')
	{
		(*comma_counter) += 1;
		y = 1;
		while (path[*x + y] == ' ')
			y++;
		if (path[*x + y] == ',')
			simple_exit("Error\nInvalid color path\n", game);
	}
}

static int	check_commas_digits(char c, int *nc, int *cc, int *x)
{
	if (c == ',')
	{
		*cc += 1;
		(*x)++;
		return (SUCCESS);
	}
	else if (c >= '0' || c <= '9')
	{
		*nc += 1;
		(*x)++;
		return (SUCCESS);
	}
	else if (*cc == 2)
	{
		while (c)
		{
			while (c == ' ')
				(*x)++;
			if (!c || !((c >= '0' && c <= '9')))
				return (FAILURE);
			(*x)++;
		}
	}
	return (SUCCESS);
}

static void	order_check(char *path, t_game *game)
{
	int	x;
	int	num_count;
	int	com_count;
	int	result;

	x = 0;
	num_count = 0;
	com_count = 0;
	while (path[x])
	{
		while (path[x] == ' ')
			x++;
		if (path[x] == ',' && num_count == 0)
			simple_exit("Error\nInvalid color path ORDER CHECK\n", game);
		result = check_commas_digits(path[x], &num_count, &com_count, &x) == 1;
		if (result == FAILURE)
			simple_exit("Error\nInvalid color path END LINE\n", game);
		x++;
	}
}

static void	color_path_check(char *path, t_game *game)
{
	int	x;
	int	comma_counter;
	int	number_counter;

	printf("[DEBUG] in color_path_check %s\n", path);
	x = 0;
	comma_counter = 0;
	number_counter = 0;
	while (path[x])
	{
		comma_check(path, &x, &comma_counter, game);
		if (path[x] >= '0' && path[x] <= '9')
			number_counter += 1;
		else if (!((path[x] >= '0' && path[x] <= '9') || path[x] == ' '
				|| path[x] == ','))
			simple_exit("Error\nInvalid color path ELSE IF\n", game);
		x++;
	}
	if (comma_counter != 2 || number_counter < 3 || number_counter > 9)
		simple_exit("Error\nInvalid color pathNUMBER\n", game);
	order_check(path, game);
}

void	color_check(t_game *game)
{
	char	**f_color;
	char	**c_color;

	color_path_check(game->file.f_path, game);
	color_path_check(game->file.c_path, game);
	f_color = ft_split(game->file.f_path, ',', game);
	c_color = ft_split(game->file.c_path, ',', game);
	game->floor[0] = ft_simple_atoi(f_color[0], game);
	game->floor[1] = ft_simple_atoi(f_color[1], game);
	game->floor[2] = ft_simple_atoi(f_color[2], game);
	game->ceiling[0] = ft_simple_atoi(c_color[0], game);
	game->ceiling[1] = ft_simple_atoi(c_color[1], game);
	game->ceiling[2] = ft_simple_atoi(c_color[2], game);
	if (game->floor[0] > 255 || game->floor[1] > 255 || game->floor[2] > 255
		|| game->ceiling[0] > 255 || game->ceiling[1] > 255
		|| game->ceiling[2] > 255)
		simple_exit("Error\nInvalid color\n", game);
}
