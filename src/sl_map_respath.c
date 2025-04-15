/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_map_respath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:25:49 by abollia           #+#    #+#             */
/*   Updated: 2025/03/21 14:01:46 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**sl_map_copy(t_data *data)
{
	int		i;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * (data->map.line_count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data->map.line_count)
	{
		copy[i] = ft_strdup(data->map.pattern[i]);
		if (!copy[i])
		{
			ft_ffa(copy);
			sl_exit_handler("Error - Malloc (map copy)", 1, NULL, data);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	sl_flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	sl_flood_fill(map, x + 1, y);
	sl_flood_fill(map, x - 1, y);
	sl_flood_fill(map, x, y + 1);
	sl_flood_fill(map, x, y - 1);
}

static int	sl_map_ispathvalid(char **copy, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'C' || copy[y][x] == 'E')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	sl_map_respath(t_data *data)
{
	char	**copy;
	int		x;
	int		y;

	copy = sl_map_copy(data);
	if (!copy)
		return (sl_map_error("Malloc (map copy)"));
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'P')
			{
				sl_flood_fill(copy, x, y);
				break ;
			}
			x++;
		}
		y++;
	}
	if (sl_map_ispathvalid(copy, data))
		return (ft_ffa(copy), 1);
	return (ft_ffa(copy), 0);
}
