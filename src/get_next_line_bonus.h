/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:29:00 by cborrome          #+#    #+#             */
/*   Updated: 2025/06/09 14:34:32 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include "cub3d.h"
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd, t_game *game);
char	*ft_fill_line_gnl(int fd, char *line, t_game *game);
char	*ft_next_line_gnl(char *line, t_game *game);
char	*ft_remaining_line_gnl(char *line, t_game *game);
char	*ft_strchr_gnl(char *string, int c);
size_t	ft_strlen_gnl(char *s);
char	*ft_strjoin_gnl(char *str1, char *buffer, t_game *game);

#endif
