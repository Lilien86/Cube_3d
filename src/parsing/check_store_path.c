/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_store_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:07:51 by lauger            #+#    #+#             */
/*   Updated: 2024/09/23 13:41:51 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	return (0);
}

int	check_path(t_read_file *rf, int num_line, char *id)
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
	if (has_extenssion(str, ".xpm") == false && has_extenssion(str, ".png") == false)
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
