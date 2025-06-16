/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:52:43 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/16 14:12:30 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*destination;
	char	*source;

	if (dst == NULL && src == NULL)
		return (0);
	i = 0;
	destination = (char *)dst;
	source = (char *)src;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dst);
}

static void	check_split_numbers(const char *src, t_game *game, int start,
		int end)
{
	int	i;
	int	in_number;
	int	temp;

	i = start;
	in_number = 0;
	while (i < end && src[i] == ' ')
		i++;
	while (i < end)
	{
		if (src[i] >= '0' && src[i] <= '9')
			in_number = 1;
		else if (src[i] == ' ' && in_number)
		{
			temp = i;
			while (temp < end && src[temp] == ' ')
				temp++;
			if (temp < end && src[temp] >= '0' && src[temp] <= '9')
				simple_exit("Error\nInvalid color\n", game);
			in_number = 0;
		}
		else if (src[i] == ',')
			in_number = 0;
		i++;
	}
}

char	*ft_strdup_color(const char *s, t_game *game, int start, int end)
{
	char	*src;
	char	*scopy;
	int		x;

	x = 0;
	src = (char *)s;
	check_split_numbers(src, game, start, end);
	scopy = (char *)arena_alloc(game->arena, ((end - start) + 1)
			* sizeof(char));
	while (src[end - 1] == ' ')
		end--;
	while (start < end)
	{
		while (start < end && src[start] == ' ')
			start++;
		if (start < end)
			scopy[x++] = src[start++];
	}
	scopy[x] = '\0';
	return (scopy);
}

int	ft_simple_atoi(const char *str, t_game *game)
{
	int	result;
	int	i;
	int	x;

	result = 0;
	i = 0;
	x = 0;
	if (!str)
		return (256);
	while (str[x])
	{
		if (str[x] < '0' || str[x] > '9')
			simple_exit("Error\nInvalid color\n", game);
		x++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i = i + 1;
	}
	return (result);
}
