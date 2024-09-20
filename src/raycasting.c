#include "cub3d.h"


void dda_algo(t_ray *ray)
{
		while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->int_map[ray->map_x][ray->map_y] > 0)
			ray->hit = 1;
	}
}

//func for check wich side choose for the texure line
//trabsform xpm load to get data adrresse

// static void draw_texture(t_ray *ray, int x)
// {
//     int y;
//     int color;
//     int tex_y;
//     int d;

//     y = ray->draw_start;
//     while (y <= ray->draw_end)
//     {
//         d = y * 256 - SCREEN_HEIGHT * 128 + ray->line_height * 128;
//         tex_y = ((d * ray->texture->height) / ray->line_height) / 256;
//         if (tex_y < 0)
//             tex_y = 0;
//         if (tex_y >= ray->texture->height)
//             tex_y = ray->texture->height - 1;

//         color = *(int *)(ray->texture->pixels + (tex_y * ray->texture->size_line + ray->tex_x * (ray->texture->bpp / 8)));
//         *(int *)(mlx->img->pixels + (y * mlx->img->size_line + x * (mlx->img->bpp / 8))) = color;
//         y++;
//     }
// }

int render_next_frame(t_ray *ray)
{
	int x;
	int i;
	
	x = 0;
	i = 0;

	while (x < SCREEN_WIDTH)
	{
		calculate_ray(ray, &x);
		dda_algo(ray);
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		else
			ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);

		ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
		ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray->draw_end >= SCREEN_HEIGHT)
			ray->draw_end = SCREEN_HEIGHT - 1;

		
		// int tex_num = ray->int_map[ray->map_x][ray->map_y] - 1;

		// double wall_x;
		// if (ray->side == 0) wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
		// else           wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
		// wall_x -= floor((wall_x));

		// int tex_x;
		// tex_x = (int)(wall_x * (double)TEX_WIDTH);
		// if(ray->side == 0 && ray->ray_dir_x > 0) tex_x = TEX_WIDTH - tex_x - 1;
		// if(ray->side == 1 && ray->ray_dir_y < 0) tex_x = TEX_WIDTH - tex_x - 1;

		// double step = 1.0 * TEX_HEIGHT / ray->line_height;
		// double tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
		// for(int y = ray->draw_start; y < ray->draw_end; y++)
		// { 
		//     int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		//     tex_pos += step;
		//     int color = texture[0][TEX_HEIGHT * tex_y + tex_x];
		//     if(ray->side == 1) color = (color >> 1) & 8355711;
		//     buffer[y][x] = color;
		// }

		put_ray_colors(ray, &x);
		x++;
	}
	ray->old_time = ray->time;
	ray->time = get_current_time_millis();
	ray->frame_time = (ray->time - ray->old_time) / 1000.0;
	if (ray->frame_time > 0)
		//printf("FPS: %f\n", 1.0 / ray->frame_time);
	mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img, 0, 0);
	ray->move_speed = ray->frame_time * 5.0;
	ray->rot_speed = ray->frame_time * 3.0;
	return (0);
}

void put_ray_colors(t_ray *ray, int *x)
{
	int i;

	if (ray->int_map[ray->map_x][ray->map_y] == 1)
		ray->wall_color = 0xCDC1FF;
	if (ray->side == 1)
		ray->wall_color = 0xF5EFFF;
	i = ray->draw_start;
	while(i <= ray->draw_end)
	{
		ray->addr[i * ray->line_length / 4 + *x] = ray->wall_color;
		i++;
	}
	i = ray->draw_end;
	ray->floor_color = ray->data->f_hex_rgb;
	while(i <= SCREEN_HEIGHT)
	{
		ray->addr[i * ray->line_length / 4 + *x] = ray->floor_color;
		i++;
	}
	i = ray->draw_start;
	ray->ceilling_color = ray->data->c_hex_rgb;
	while(i >= 0)
	{
		ray->addr[i * ray->line_length / 4 + *x] = ray->ceilling_color;
		i--;
	}
}
