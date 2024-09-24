#include "cub3d.h"

static void set_player_pos_NS(t_ray *ray, char direction)
{
	if (direction == 'N')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	else if (direction == 'S')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
}

static void set_player_pos_EW(t_ray *ray, char direction)
{
	if (direction == 'E')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plane_x = 0.66;
		ray->plane_y = 0;
	}
	else if (direction == 'W')
	{	
		ray->dir_x = 0;
		ray->dir_y = -1 ;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
}

void set_player_position(t_ray *ray, int x, int y, char direction)
{
    ray->pos_x = y + 0.5;
	ray->pos_y = x + 0.5;
    set_player_pos_NS(ray, direction);
    set_player_pos_EW(ray, direction);
}
