#include "cub3d.h"

static void	free_img_mlx_error(t_ray *ray, t_data *data)
{
	printf(RED"Error:\nimage paths is incorrect\n"WHITE);
	if (ray->tx_north->img)
		mlx_destroy_image(ray->mlx, ray->tx_north->img);
	if (ray->tx_south->img)
		mlx_destroy_image(ray->mlx, ray->tx_south->img);
	if (ray->tx_west->img)
		mlx_destroy_image(ray->mlx, ray->tx_west->img);
	if (ray->tx_east->img)
		mlx_destroy_image(ray->mlx, ray->tx_east->img);
	if (data->ray->mlx)
		mlx_destroy_display(data->ray->mlx);
	if (ray->tx)
		free(ray->tx);
	if (ray->tx_north)
		free(ray->tx_north);
	if (ray->tx_south)
		free(ray->tx_south);
	if (ray->tx_west)
		free(ray->tx_west);
	if (ray->tx_east)
		free(ray->tx_east);
	free(data->ray->mlx);
	ft_free_tab_int(data->ray->int_map, data->map_height);
	free(data->ray);
	pars_clean_exit(data);
	exit(0);
}

void	paths_to_mlx_image(t_ray *ray, t_data *data)
{
	if (!data || !ray)
		return ;
	//ray->tx = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	ray->tx_north = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	ray->tx_south = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	ray->tx_west = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	ray->tx_east = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	ray->tx_north->img = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_north, &ray->tx_north->width, &ray->tx_north->height);
	ray->tx_south->img = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_south, &ray->tx_south->width, &ray->tx_south->height);
	ray->tx_west->img = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_west, &ray->tx_west->width, &ray->tx_west->height);
	ray->tx_east->img = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_east, &ray->tx_east->width, &ray->tx_east->height);
	if (ray->tx_north->img == NULL || ray->tx_south->img == NULL || ray->tx_west->img == NULL || ray->tx_east->img == NULL)
	{
		free_img_mlx_error(ray, data);
	}
	ray->tx_north->addr = mlx_get_data_addr(ray->tx_north->img, &ray->tx_north->bpp, &ray->tx_north->size_line, &ray->tx_north->endian);
	ray->tx_south->addr = mlx_get_data_addr(ray->tx_south->img, &ray->tx_south->bpp, &ray->tx_south->size_line, &ray->tx_south->endian);
	ray->tx_west->addr = mlx_get_data_addr(ray->tx_west->img, &ray->tx_west->bpp, &ray->tx_west->size_line, &ray->tx_west->endian);
	ray->tx_east->addr = mlx_get_data_addr(ray->tx_east->img, &ray->tx_east->bpp, &ray->tx_east->size_line, &ray->tx_east->endian);
}

void	init_ray(t_ray *ray, t_data *data, int **int_map)
{
	if (!ray)
	{
		ft_printf("Error\nmalloc() failed\n", 2);
		exit(1);
	}
	ray->time = 0;
	ray->old_time = 0;
	parse_map(ray, data, int_map);
	ray->int_map = int_map;
	data->ray = ray;
	ray->data = data;
}

int	clean_close_windows(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_destroy_image(data->ray->mlx, data->ray->tx_north->img);
	mlx_destroy_image(data->ray->mlx, data->ray->tx_south->img);
	mlx_destroy_image(data->ray->mlx, data->ray->tx_west->img);
	mlx_destroy_image(data->ray->mlx, data->ray->tx_east->img);
	free(data->ray->tx_north);
	free(data->ray->tx_south);
	free(data->ray->tx_west);
	free(data->ray->tx_east);
	if (data->ray->img)
		mlx_destroy_image(data->ray->mlx, data->ray->img);
	if (data->ray->mlx)
		mlx_destroy_window(data->ray->mlx, data->ray->mlx_win);
	if (data->ray->mlx)
		mlx_destroy_display(data->ray->mlx);
	ft_free_tab_int(data->ray->int_map, data->map_height);
	free(data->ray->mlx);
	free(data->ray);
	pars_clean_exit(data);
	return (0);
}

int		setup_mlx(t_ray *ray)
{
	ray->mlx = mlx_init();
	if (ray->mlx == NULL)
	{
		printf("Error:mlx_init() failed\n");
		return (1);
	}
	paths_to_mlx_image(ray, ray->data);
	ray->mlx_win = mlx_new_window(ray->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!ray->mlx_win)
	{
		free(ray->mlx_win);
		printf("Error:mlx_new_window() failed\n");
		return (1);
	}
	ray->img = mlx_new_image(ray->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ray->addr = mlx_get_data_addr(ray->img, &ray->bpp,
			&ray->size_line, &ray->endian);
	ray->addr_c = (int *)mlx_get_data_addr(ray->img, &ray->bpp_c, \
	&ray->size_line_c, &ray->endian_c);
	mlx_hook(ray->mlx_win, 2, 1L << 0, key_hook, ray);
	mlx_loop_hook(ray->mlx, render_next_frame, ray);
	mlx_hook(ray->mlx_win, 17, 0, clean_close_windows, ray->data);
	mlx_loop(ray->mlx);
	return (0);
}
