#include "cub3D.h"

static void	fps(t_vars *cub)
{
	int	fps;

	fps = time(NULL);
	if (cub->temp != fps)
	{
		cub->temp = fps;
		fps = cub->i;
		if (cub->fps)
			free(cub->fps);
		cub->fps = ft_itoa(fps);
		cub->i = 1;
	}
	else
	{
		cub->i++;
	}
}

int	multithread(t_vars *cub)
{
	pthread_t	threads[4];
	t_thread	thread_data[4];
	int			i;

	i = -1;
	while (++i < 4)
	{
		thread_data[i].cub = (*cub);
		thread_data[i].thread_num = i;
		if ((pthread_create(&threads[i], NULL, \
			graphical_loop, &thread_data[i])) != 0)
			return (0);
	}
	i = -1;
	while (++i < 4)
		pthread_join(threads[i], NULL);
	return (1);
}

int	frame(t_vars *cub)
{
	fps(cub);
	cub->ray_c.free_win = 1;
	move(cub);
	rotate(cub);
	if (cub->ray_c.key.exit == 1)
	{
		ft_exit(cub);
		return (0);
	}
	cub->ray_c.ray_dir = rotation_z(cub, (t_vector){0, -1, 0});
	if (!(create_plans_sprite(cub)))
		return (0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, cub->ray_c.win);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, cub->ray_c.img);
	mlx_do_sync(cub->ray_c.mlx);
	if (!(multithread(cub)))
		return (0);
	mlx_put_image_to_window(cub->ray_c.mlx, cub->ray_c.win, \
							cub->ray_c.img, 0, 0);
	mlx_string_put(cub->ray_c.mlx, cub->ray_c.win, 30, 30, 13979169, cub->fps);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, cub->ray_c.win);
	return (1);
}
