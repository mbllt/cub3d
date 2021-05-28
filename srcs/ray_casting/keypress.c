#include "cub3D.h"

int	key_press(int key, t_vars *cub)
{
	if (key == O)
		cub->ray_c.key.up = 1;
	if (key == L)
		cub->ray_c.key.down = 1;
	if (key == W)
		cub->ray_c.key.forward = 1;
	if (key == S)
		cub->ray_c.key.backward = 1;
	if (key == D)
		cub->ray_c.key.right = 1;
	if (key == A)
		cub->ray_c.key.left = 1;
	if (key == KEYUP)
		cub->ray_c.key.rot_x_left = 1;
	if (key == KEYDOWN)
		cub->ray_c.key.rot_x_right = 1;
	if (key == KEYLEFT)
		cub->ray_c.key.rot_z_left = 1;
	if (key == KEYRIGHT)
		cub->ray_c.key.rot_z_right = 1;
	if (key == 53)
	{
		cub->ray_c.key.exit = 1;
		cub->exit_good = 1;
	}
	if (key == JUMP)
		cub->ray_c.key.jump = 1;
	if (key == SPEED)
		cub->ray_c.key.speed = 1;
	return (1);
}

int	key_release(int key, t_vars *cub)
{
	if (key == O)
		cub->ray_c.key.up = 0;
	if (key == L)
		cub->ray_c.key.down = 0;
	if (key == W)
		cub->ray_c.key.forward = 0;
	if (key == S)
		cub->ray_c.key.backward = 0;
	if (key == D)
		cub->ray_c.key.right = 0;
	if (key == A)
		cub->ray_c.key.left = 0;
	if (key == KEYLEFT)
		cub->ray_c.key.rot_z_left = 0;
	if (key == KEYRIGHT)
		cub->ray_c.key.rot_z_right = 0;
	if (key == KEYUP)
		cub->ray_c.key.rot_x_left = 0;
	if (key == KEYDOWN)
		cub->ray_c.key.rot_x_right = 0;
	if (key == JUMP)
		cub->ray_c.key.jump = 0;
	if (key == SPEED)
		cub->ray_c.key.speed = 0;
	return (1);
}

static void	move_bis(t_vars *cub, t_vector temp_dir_ray)
{
	if (cub->ray_c.key.up == 1 && cub->parsing.pz + MOVE_SPEED < 1)
		cub->parsing.pz += MOVE_SPEED;
	if (cub->ray_c.key.down == 1 && cub->parsing.pz + MOVE_SPEED > 0.5)
		cub->parsing.pz -= MOVE_SPEED;
	if (cub->ray_c.key.jump == 1 && cub->parsing.pz + MOVE_SPEED < 0.85)
		cub->parsing.pz += MOVE_SPEED;
	if (cub->ray_c.key.jump == 0 && cub->parsing.pz + MOVE_SPEED > 0.5)
		cub->parsing.pz -= MOVE_SPEED;
	if (cub->ray_c.key.right == 1 && check_collision(cub, temp_dir_ray, 2) == 1)
	{
		if (cub->ray_c.key.speed == 1)
		{
			cub->parsing.px -= temp_dir_ray.y * MOVE_SPEED * 2;
			cub->parsing.py += temp_dir_ray.x * MOVE_SPEED * 2;
		}
		cub->parsing.px -= temp_dir_ray.y * MOVE_SPEED;
		cub->parsing.py += temp_dir_ray.x * MOVE_SPEED;
	}
	if (cub->ray_c.key.left == 1 && check_collision(cub, temp_dir_ray, 3) == 1)
	{
		if (cub->ray_c.key.speed == 1)
		{
			cub->parsing.px += temp_dir_ray.y * MOVE_SPEED * 2;
			cub->parsing.py -= temp_dir_ray.x * MOVE_SPEED * 2;
		}
		cub->parsing.px += temp_dir_ray.y * MOVE_SPEED;
		cub->parsing.py -= temp_dir_ray.x * MOVE_SPEED;
	}
}

void	move(t_vars *cub)
{
	t_vector	temp_dir_ray;

	temp_dir_ray = cub->ray_c.ray_dir;
	temp_dir_ray = rotation_z(cub, (t_vector){0, -1, 0});
	if (cub->ray_c.key.forward == 1 && check_collision(cub, temp_dir_ray, \
		0) == 1)
	{
		if (cub->ray_c.key.speed == 1)
		{
			cub->parsing.px += temp_dir_ray.x * MOVE_SPEED * 2;
			cub->parsing.py += temp_dir_ray.y * MOVE_SPEED * 2;
		}
		cub->parsing.px += temp_dir_ray.x * MOVE_SPEED;
		cub->parsing.py += temp_dir_ray.y * MOVE_SPEED;
	}
	if (cub->ray_c.key.backward == 1 && check_collision(cub, temp_dir_ray, \
		1) == 1)
	{
		if (cub->ray_c.key.speed == 1)
		{
			cub->parsing.px -= temp_dir_ray.x * MOVE_SPEED * 2;
			cub->parsing.py -= temp_dir_ray.y * MOVE_SPEED * 2;
		}
		cub->parsing.px -= temp_dir_ray.x * MOVE_SPEED;
		cub->parsing.py -= temp_dir_ray.y * MOVE_SPEED;
	}
	move_bis(cub, temp_dir_ray);
}

void	rotate(t_vars *cub)
{
	if (cub->ray_c.key.rot_x_right == 1)
	{
		if (cub->ray_c.rota_x + MOVE_SPEED < 0.7)
		{
			cub->ray_c.rota_x += MOVE_SPEED;
			init_matrix_x(cub);
		}
	}
	if (cub->ray_c.key.rot_x_left == 1)
	{
		if (cub->ray_c.rota_x - MOVE_SPEED > -0.7)
		{
			cub->ray_c.rota_x -= MOVE_SPEED;
			init_matrix_x(cub);
		}
	}
	if (cub->ray_c.key.rot_z_right == 1)
	{
		if (cub->ray_c.rota_z + MOVE_SPEED > 360 * (M_PI / 180))
			cub->ray_c.rota_z -= 360 * (M_PI / 180);
		cub->ray_c.rota_z += MOVE_SPEED;
		init_matrix_z(cub);
	}
	if (cub->ray_c.key.rot_z_left == 1)
	{
		if (cub->ray_c.rota_z - MOVE_SPEED < - (360 * (M_PI / 180)))
			cub->ray_c.rota_z += 360 * (M_PI / 180);
		cub->ray_c.rota_z -= MOVE_SPEED;
		init_matrix_z(cub);
	}
}
