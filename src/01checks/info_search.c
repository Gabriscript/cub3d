#include "cub3d.h"

static void	color_check(t_game *game)
{
	char	**f_color;
	char	**C_color;

	f_color = ft_split(game->file.f_path, ',', game);
	C_color = ft_split(game->file.c_path, ',', game);
	game->file.f_r = ft_simple_atoi(f_color[0], game);		
	game->file.f_g = ft_simple_atoi(f_color[1], game);
	game->file.f_b = ft_simple_atoi(f_color[2], game);
	game->file.c_r = ft_simple_atoi(C_color[0], game);
	game->file.c_g = ft_simple_atoi(C_color[1], game);
	game->file.c_b = ft_simple_atoi(C_color[2], game);
	if (game->file.f_r > 255 || game->file.f_r > 255 || game->file.f_r > 255 || \
			game->file.f_r > 255 || game->file.f_r > 255 || game->file.f_r > 255)
		simple_exit("Error\nInvalid color\n", game);
}

static void	info_checks(t_game *game)
{
	if (game->file.no != 1 || game->file.so != 1 || game->file.we != 1 || game->file.ea != 1)
		simple_exit("Error\nMissing path identifier\n", game);
	if (game->file.f != 1 || game->file.c != 1)
		simple_exit("Error\nMissing color identifier\n", game);

	//Addition
	//aggiungo qui il controllo se il file della PATH esiste???
	//path_check();
	color_check(game);
}

static void	cub_map_part(t_game *game, int *y)
{
	int	map_len;

	map_len = game->file.total_file_len - (*y);
	game->file.full_map = arena_alloc(game->arena, map_len + 1);
	ft_memcpy(game->file.full_map, game->file.full_file_one_line + (*y), map_len);
	game->file.full_map[map_len] = '\0';
	if (ft_strlen(game->file.full_map) < 11)
		simple_exit("Error\nNot a proper map\n", game);
	game->file.full_map_zero_check = arena_alloc(game->arena, map_len + 1);
	ft_memcpy(game->file.full_map_zero_check, game->file.full_file_one_line + (*y), map_len);
	game->file.full_map[map_len] = '\0';
}

void	info_search(t_game *game)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while(game->file.full_file_one_line[i])
	{
		if (game->file.no == 1 && game->file.so == 1 && \
			game->file.we == 1 && game->file.ea == 1 && game->file.f == 1 \
			&& game->file.c == 1)
				if (y == 0)
					y = i;
		while (game->file.full_file_one_line[i] == '\n' ||
			   game->file.full_file_one_line[i] == ' ')
			i++;
		if (find_path_1(game, &i) == 1)
			continue;
		else if (find_path_2(game, &i) == 1)
			continue;
		else if (find_color(game, &i) == 1)
			continue;
		i++;
	}
	info_checks(game);
	cub_map_part(game, &y);
}
