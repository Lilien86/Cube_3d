
#include "../cub3d.h"

int	check_line(t_read_file *rf, char *id, int num_line, int value_check)
{
	int		result;
	char	*line;

	result = 0;
	line = NULL;
	line = deblank(rf->tab_content[num_line]);
	if (rf == NULL || ft_strlen(id) < (size_t)value_check || !line)
		return (-2);
	//printf("=====%c\n", line[value_check]);
	result = ft_strncmp(line, id, value_check);
	free(line);
	return (result);
}

static int	check_path_second_part(char *id, t_read_file *rf, char *str)
{
	if (ft_strcmp(id, "NO") == 0)
	{
		if (rf->p_north != NULL)
			return (-1);
		rf->p_north = str;
	}
	else if (ft_strcmp(id, "SO") == 0)
	{
		if (rf->p_south != NULL)
			return (-1);
		rf->p_south = str;
	}
	else if (ft_strcmp(id, "WE") == 0)
	{
		if (rf->p_west != NULL)
			return (-1);
		rf->p_west = str;
	}
	else if (ft_strcmp(id, "EA") == 0)
	{
		if (rf->p_east != NULL)
			return (-1);
		rf->p_east = str;
	}
	//free(line);
	return (0);
}

static int	check_path(t_read_file *rf, int num_line, char *id)
{
	char	*str;
	char	*line;

	if (rf == NULL)
		pars_clean_exit(rf->data);
	line = deblank(rf->tab_content[num_line]);
	if (!line)
		return (-1);
	str = ft_substr(line, 2, ft_strlen(line) - 2);
	if (str == NULL)
		return (-1);
	if (has_extenssion(str, ".xpm") == false)
	{
		free(str);
		free(line);
		return (-1);
	}
	if (check_path_second_part(id, rf, str) == -1)
	{
		free(line);
		free(str);
		return (-1);
	}
	free(line);
	return (0);
}

static int	valid_value(t_data *data, char *id, int i)
{
	if (ft_strstr(data->read_file->tab_content[i], id))
	{
		if (check_line(data->read_file, id, i, 2) != 0)
		{
			ft_printf(RED "Error:\nFile format is incorect\n" WHITE);
			pars_clean_exit(data);
		}
		if (check_path(data->read_file, i, id) != 0)
		{
			ft_printf(RED "Error:\nFile not have the extenssion .xpm\n" WHITE);
			pars_clean_exit(data);
		}
	}
	return (0);
}

static void	grab_sprite_paths(t_data *data)
{
	int	i;

	i = 0;
	if (data->read_file == NULL)
		pars_clean_exit(data);
	while (data->read_file->tab_content[i])
	{
		valid_value(data, "NO", i);
		valid_value(data, "SO", i);
		valid_value(data, "WE", i);
		valid_value(data, "EA", i);
		i++;
	}
		return ;
}

void	grab_data(t_data *data)
{
	char	**c_map;

	if (!data || data == NULL)
		return ;
	grab_sprite_paths(data);
	grab_color(data);
	grab_map(data);
	replace_space_to_wall(data);
	c_map = ft_copy_tab(data->map, ft_tab_len(data->map));
	if (c_map == NULL)
		return ;
	manage_utilization_flood_fill(data, c_map);
	open_textures_paths(data, c_map);
	ft_free_tab(c_map);
	return ;
}
