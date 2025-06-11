#include "cub3d.h"

static void	path_check(char *path_str, t_game *game)
{
	int	path_len;
	int	fd;

	path_len = ft_strlen(path_str);
	if (path_len < 4 || ft_strcmp(path_str + path_len - 4, ".xpm") != 0)
		simple_exit("Error\nTexture must be .xpm file\n", game);
	fd = open(path_str, O_RDONLY);
	if (fd == -1)
	{
		simple_exit("Error\nError on opening the picture\n", game);
	}
	close(fd);
}

static void	info_checks(t_game *game)
{
	if (game->file.no != 1 || game->file.so != 1
		|| game->file.we != 1 || game->file.ea != 1)
		simple_exit("Error\nMissing path identifier\n", game);
	if (game->file.f != 1 || game->file.c != 1)
		simple_exit("Error\nMissing color identifier\n", game);
	path_check(game->file.no_path, game);
	path_check(game->file.so_path, game);
	path_check(game->file.we_path, game);
	path_check(game->file.ea_path, game);
	color_check(game);
}

static void	cub_map_part(t_game *game, int *y)
{
	int	map_len;

	map_len = game->file.total_file_len - (*y);
	game->file.full_map = arena_alloc(game->arena, map_len + 1);
	ft_memcpy(game->file.full_map, game->file.full_file_one_line
		+ (*y), map_len);
	game->file.full_map[map_len] = '\0';
	if (ft_strlen(game->file.full_map) < 11)
		simple_exit("Error\nNot a proper map\n", game);
	game->file.full_map_flood_fill = arena_alloc(game->arena, map_len + 1);
	ft_memcpy(game->file.full_map_flood_fill, game->file.full_file_one_line
		+ (*y), map_len);
	game->file.full_map_flood_fill[map_len] = '\0';
}

void	info_search(t_game *game)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (game->file.full_file_one_line[i])
	{
		if (game->file.no == 1 && game->file.so == 1 && game->file.we == 1
			&& game->file.ea == 1 && game->file.f == 1 && game->file.c == 1)
			if (y == 0)
				y = i;
		while (game->file.full_file_one_line[i] == '\n'
			|| game->file.full_file_one_line[i] == ' ')
			i++;
		if (find_path_1(game, &i) == 1)
			continue ;
		else if (find_path_2(game, &i) == 1)
			continue ;
		else if (find_color(game, &i) == 1)
			continue ;
		else
			simple_exit("Error\nInvalid info part\n", game);
		i++;
	}
	info_checks(game);
	cub_map_part(game, &y);
}
