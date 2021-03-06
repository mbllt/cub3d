#include "cub3D.h"

static int	init_pixel_data(t_vars *cub)
{
	int	i;

	cub->pixel_data = malloc(sizeof(unsigned int *) * cub->parsing.rx);
	if (!cub->pixel_data)
		return (0);
	i = -1;
	while (++i < cub->parsing.rx)
	{
		cub->pixel_data[i] = malloc(sizeof(unsigned int) * cub->parsing.ry);
		if (!cub->pixel_data[i])
		{
			while (--i >= 0)
				if (cub->pixel_data[i])
					free(cub->pixel_data[i]);
			free(cub->pixel_data);
			return (0);
		}
	}
	return (1);
}

static void	init_info_bitmap(t_vars *cub)
{
	cub->save.header_bitmap.size = 40;
	cub->save.header_bitmap.width = cub->parsing.rx;
	cub->save.header_bitmap.height = cub->parsing.ry;
	cub->save.header_bitmap.planes = 1;
	cub->save.header_bitmap.bpp = 24;
	cub->save.header_bitmap.compression = 0;
	cub->save.header_bitmap.imagesize = cub->parsing.rx * cub->parsing.ry * 3;
	cub->save.header_bitmap.xpixelsperm = 0;
	cub->save.header_bitmap.ypixelsperm = 0;
	cub->save.header_bitmap.colors_used = 0;
	cub->save.header_bitmap.important_colors = 0;
}

int	init_save_image(t_vars *cub)
{
	cub->save.signature[0] = 'B';
	cub->save.signature[1] = 'M';
	cub->save.file_size = cub->parsing.rx * cub->parsing.ry * 4 + 54;
	cub->save.reserved = 0;
	cub->save.data_offset = 40 + 14;
	init_info_bitmap(cub);
	if (!(init_pixel_data(cub)))
		return (0);
	return (1);
}
