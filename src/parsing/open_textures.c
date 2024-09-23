
#include "../cub3d.h"

static void	put_str_exit(t_data *data, char *str, char **c_map)
{
	if (!data)
		return ;
	ft_putstr_fd(str, 2);
	ft_free_tab(c_map);
	pars_clean_exit(data);
	return ;
}

static int	handle_opening_folder(t_data *data, char **c_map, char *path)
{
	int	fd;

	fd = 0;
	fd = open(path, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE, c_map);
	}
	return (fd);
}

static int	handle_opening_file(t_data *data, char **c_map, char *path)
{
	int	fd;

	fd = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE, c_map);
	if (fd != -1)
		close(fd);
	return (fd);
}

int	open_textures_paths(t_data *data, char **c_map)
{
	if (!data)
		return (-1);
	(void)c_map;
	handle_opening_folder(data, c_map, data->read_file->p_north);
	handle_opening_folder(data, c_map, data->read_file->p_south);
	handle_opening_folder(data, c_map, data->read_file->p_west);
	handle_opening_folder(data, c_map, data->read_file->p_east);

	handle_opening_file(data, c_map, data->read_file->p_north);
	handle_opening_file(data, c_map, data->read_file->p_south);
	handle_opening_file(data, c_map, data->read_file->p_west);
	handle_opening_file(data, c_map, data->read_file->p_east);
	return (0);
}