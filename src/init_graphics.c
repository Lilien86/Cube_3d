/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:52:58 by lauger            #+#    #+#             */
/*   Updated: 2024/09/24 13:42:26 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

void	paths_to_mlx_image(t_ray *r, t_data *data)
{
	if (!data || !r)
		return ;
	r->tx = NULL;
	r->tx_north = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	r->tx_south = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	r->tx_west = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	r->tx_east = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	r->tx_north->img = mlx_xpm_file_to_image(data->ray->mlx,
			data->rf->p_north, &r->tx_north->width, &r->tx_north->height);
	r->tx_south->img = mlx_xpm_file_to_image(data->ray->mlx,
			data->rf->p_south, &r->tx_south->width, &r->tx_south->height);
	r->tx_west->img = mlx_xpm_file_to_image(data->ray->mlx,
			data->rf->p_west, &r->tx_west->width, &r->tx_west->height);
	r->tx_east->img = mlx_xpm_file_to_image(data->ray->mlx,
			data->rf->p_east, &r->tx_east->width, &r->tx_east->height);
	if (r->tx_north->img == NULL || r->tx_south->img == NULL
		|| r->tx_west->img == NULL || r->tx_east->img == NULL)
		free_img_mlx_error(r, data);
	r->tx_north->addr = mlx_get_data_addr(r->tx_north->img, &r->tx_north->bpp,
			&r->tx_north->size_line, &r->tx_north->endian);
	r->tx_south->addr = mlx_get_data_addr(r->tx_south->img,
			&r->tx_south->bpp, &r->tx_south->size_line, &r->tx_south->endian);
	r->tx_west->addr = mlx_get_data_addr(r->tx_west->img,
			&r->tx_west->bpp, &r->tx_west->size_line, &r->tx_west->endian);
	r->tx_east->addr = mlx_get_data_addr(r->tx_east->img,
			&r->tx_east->bpp, &r->tx_east->size_line, &r->tx_east->endian);
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

int	setup_mlx(t_ray *ray)
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
