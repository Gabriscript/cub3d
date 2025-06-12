/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:52:37 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/12 09:52:38 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	simple_exit(char *message, t_game *game)
{
	ft_putstr_fd(message, 2);
	arena_destroy(game->arena);
	exit(EXIT_FAILURE);
}
