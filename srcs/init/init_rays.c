#include "cub3D.h"

void	init_rays(t_vars *cub, int width, int height, t_ray *ray_c)
{
	int	i;
	int	j;

	(void)cub;
	ray_c->fov = 60.0 * (M_PI / 180.0);
	if (height < width)
		ray_c->ratio = 2.0 * tan(ray_c->fov * 0.5) / width;
	else
		ray_c->ratio = 2.0 * tan(ray_c->fov * 0.5) / height;
	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < height)
		{
			ray_c->stock_rays[i][j].x = (i - width * 0.5) * ray_c->ratio;
			ray_c->stock_rays[i][j].y = -1;
			ray_c->stock_rays[i][j].z = (height * 0.5 - j) * ray_c->ratio;
			ray_c->stock_rays[i][j] = normalisation_v(ray_c->stock_rays[i][j]);
		}
	}
}
