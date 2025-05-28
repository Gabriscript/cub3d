#include "cub3d.h"

void	close_window(void *param)
{
	mlx_t *mlx = (mlx_t *)param;
	mlx_close_window(mlx);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t *mlx = (mlx_t *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}