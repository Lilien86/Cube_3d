/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains_only_these_caractere.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:38:17 by lauger            #+#    #+#             */
/*   Updated: 2024/09/23 10:05:54 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	loop_map(char **map, int i, int j, int *player)
{
	if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
		&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
		&& map[i][j] != 'W')
		return (1);
	if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
		|| map[i][j] == 'W')
		*player += 1;
	if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
		|| map[i][j] == 'W') && map[i][j + 1] == '\0')
		return (2);
	return (0);
}

int	contains_only_these_caractere(char **map)
{
	int	i;
	int	j;
	int	player;
	int	ret;

	if (!map)
		return (-1);
	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != 0)
		{
			ret = loop_map(map, i, j, &player);
			if (ret == 1)
				return (1);
			else if (ret == 2)
				return (2);
			j++;
		}
		i++;
	}
	if (player > 1 || player == 0)
		return (1);
	return (0);
}
