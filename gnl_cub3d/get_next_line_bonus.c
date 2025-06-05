/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:40:45 by cborrome          #+#    #+#             */
/*   Updated: 2025/01/29 14:03:50 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*output;
	static char	*string[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	string[fd] = ft_fill_line_gnl(fd, string[fd]);
	if (string[fd] == NULL)
	{
		return (NULL);
	}
	output = ft_next_line_gnl(string[fd]);
	if (!output)
	{
		free(string[fd]);
		return (NULL);
	}
	string[fd] = ft_remaining_line_gnl(string[fd]);
	return (output);
}

char	*ft_fill_line_gnl(int fd, char *line)
{
	char	*buffer;
	ssize_t	dimension;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	dimension = 1;
	while ((ft_strchr_gnl(line, '\n')) == NULL && dimension > 0)
	{
		dimension = read(fd, buffer, BUFFER_SIZE);
		if (dimension == -1)
		{
			free (buffer);
			return (NULL);
		}
		if (dimension == 0 && (line == NULL || line[0] == '\0'))
			break ;
		buffer[dimension] = '\0';
		line = ft_strjoin_gnl(line, buffer);
		if (line == NULL)
			break ;
	}
	free (buffer);
	return (line);
}

char	*ft_next_line_gnl(char *line)
{
	int		i;
	char	*newstring;

	i = 0;
	if (line[i] == 0)
		return (NULL);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	newstring = (char *)malloc(sizeof(char) * (i + 2));
	if (!newstring)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		newstring[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		newstring[i] = '\n';
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}

char	*ft_remaining_line_gnl(char *line)
{
	char	*str;
	int		i;
	int		k;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	str = (char *)malloc((ft_strlen_gnl(line) - i + 1) * sizeof(char));
	if (!str)
	{
		free(line);
		return (NULL);
	}
	i++;
	k = 0;
	while (line[i] != '\0')
		str[k++] = line[i++];
	str[k] = '\0';
	free(line);
	return (str);
}
