#include "cub3d.h"

int	info_path_initial_letter(int *start, char *info_line)
{
	if ((info_line[*start] == 'N' && info_line[*start + 1] == 'O')
		|| (info_line[*start] == 'S' && info_line[*start + 1] == 'O')
		|| (info_line[*start] == 'W' && info_line[*start + 1] == 'E')
		|| (info_line[*start] == 'E' && info_line[*start + 1] == 'A'))
	{
		(*start) += 2;
		while (info_line[*start] == ' ' || info_line[*start] != '\n')
			(*start)++;
		return(1);
	}
	return(0);
}
