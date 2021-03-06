#include "cub3D.h"

static int	get_nbr_sprite(t_vars *cub, char **map)
{
	int	x;
	int	y;
	int	i;

	i = 1;
	y = -1;
	while (++y < cub->parsing.map_y)
	{
		x = -1;
		while (++x < cub->parsing.map_x)
			if (map[y][x] == '2')
				i++;
	}
	return (i - 1);
}

int	init_sprite(t_vars *cub, char **world_map)
{
	int	x;
	int	y;
	int	i;

	cub->ray_c.nbr_sprite = get_nbr_sprite(cub, cub->parsing.world_map);
	cub->ray_c.sprite = malloc(sizeof(t_sprite) * cub->ray_c.nbr_sprite);
	if (!(cub->ray_c.nbr_sprite))
		return (0);
	i = 0;
	y = -1;
	while (++y < cub->parsing.map_y)
	{
		x = -1;
		while (++x < cub->parsing.map_x)
		{
			if (world_map[y][x] == '2')
			{
				cub->ray_c.sprite[i].pos.x = x + 0.5;
				cub->ray_c.sprite[i].pos.y = y + 0.5;
				cub->ray_c.sprite[i].pos.z = 0.5;
				i++;
			}
		}
	}
	return (1);
}
