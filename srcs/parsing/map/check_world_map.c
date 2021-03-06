#include "cub3D.h"

static int	check_value_in_map(t_vars *cub, char **world_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->parsing.map_y)
	{
		j = 0;
		while (j < cub->parsing.map_x)
		{
			if (world_map[i][j] && world_map[i][j] != '2' \
				&& world_map[i][j] != '1' && world_map[i][j] != '0' \
				&& world_map[i][j] != ' ' && world_map[i][j] != '\n' \
				&& (is_cardinal(world_map[i][j])) == -1)
			{
				return (0);
			}
			if (world_map[i][j] && world_map[i][j] == '2')
			{
				cub->ray_c.nbr_sprite++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_corner(t_vars *cub, char **s, int i, int j)
{
	int	start_x;
	int	end_x;
	int	start_y;
	int	end_y;
	int	k;

	k = 0;
	while (s[i][k] == ' ')
		k++;
	start_x = k;
	k = 0;
	while (s[i][cub->parsing.map_x - 1 - k] == ' ')
		k++;
	end_x = cub->parsing.map_x - 1 - k;
	k = 0;
	while (s[k][j] == ' ')
		k++;
	start_y = k;
	k = 0;
	while (s[cub->parsing.map_y - 1 - k][j] == ' ')
		k++;
	end_y = cub->parsing.map_y - 1 - k;
	if (!(check_one(s[i][start_x], s[i][end_x], s[start_y][j], s[end_y][j])))
		return (0);
	return (1);
}

static int	check_around(char **world_map, int i, int j)
{
	if (world_map[i][j - 1] == ' ' || world_map[i][j + 1] == ' ' \
		|| world_map[i - 1][j] == ' ' || world_map[i + 1][j] == ' ')
		return (0);
	return (1);
}

static int	check_zero_inside(t_vars *cub, char **world_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->parsing.map_y)
	{
		j = 0;
		while (j < cub->parsing.map_x)
		{
			if (world_map[i][j] == '0' || world_map[i][j] == '2' \
				|| (is_cardinal(world_map[i][j])) == 1)
			{
				if (!(check_corner(cub, world_map, i, j)))
				{
					return (0);
				}
				if (!(check_around(world_map, i, j)))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_world_map(t_vars *cub, char **world_map)
{
	if (!(check_value_in_map(cub, world_map)))
		return (0);
	if (!(check_zero_inside(cub, world_map)))
		return (0);
	return (1);
}
