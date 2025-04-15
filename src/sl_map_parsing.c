/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_map_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:39:22 by abollia           #+#    #+#             */
/*   Updated: 2025/03/25 13:57:12 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	sl_map_input(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->map.pattern[i])
	{
		j = 0;
		while (data->map.pattern[i][j])
		{
			if (data->map.pattern[i][j] != '0'
				&& data->map.pattern[i][j] != '1'
				&& data->map.pattern[i][j] != 'C'
				&& data->map.pattern[i][j] != 'E'
				&& data->map.pattern[i][j] != 'P'
				&& data->map.pattern[i][j] != '\n')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	sl_map_dimensions(t_data *data)
{
	int	i;

	while (data->map.pattern[data->map.height])
		data->map.height++;
	data->map.width = (int)ft_strlen(data->map.pattern[0]);
	i = 0;
	while (data->map.pattern[i])
	{
		if ((int)ft_strlen(data->map.pattern[i]) != data->map.width)
			return (sl_map_error("Map is not a rectangle"));
		i++;
	}
	if (data->map.pattern[0][data->map.width - 1] == '\n')
		data->map.width--;
	if (data->map.height < 3 || data->map.height > 20
		|| data->map.width < 3 || data->map.width > 38)
		return (sl_map_error("Invalid map size"));
	return (0);
}

static int	sl_map_elements(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->map.pattern[++i])
	{
		j = -1;
		while (data->map.pattern[i][++j])
		{
			if (data->map.pattern[i][j] == 'P')
				data->map.start_tile++;
			else if (data->map.pattern[i][j] == 'E')
				data->map.exit_tile++;
			else if (data->map.pattern[i][j] == 'C')
				data->map.collec_tile++;
		}
	}
	if (data->map.start_tile != 1)
		return (sl_map_error("Invalid start tile number"));
	if (data->map.exit_tile != 1)
		return (sl_map_error("Invalid exit tile number"));
	if (data->map.collec_tile < 1)
		return (sl_map_error("Not enough collectibles"));
	return (0);
}

static int	sl_map_walls(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->map.width)
	{
		if (data->map.pattern[0][i] != '1'
			|| data->map.pattern[data->map.height -1][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < data->map.height)
	{
		if (data->map.pattern[i][0] != '1'
			|| data->map.pattern[i][data->map.width - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	sl_map_check(t_data *data)
{
	if (!data->map.pattern || !data->map.pattern[0])
		return (sl_map_error("No map stored"));
	if (sl_map_input(data))
		return (sl_map_error("Invalid map input"));
	if (sl_map_dimensions(data))
		return (1);
	if (sl_map_elements(data))
		return (1);
	if (sl_map_walls(data))
		return (sl_map_error("Map is not surrounded by walls"));
	if (sl_map_respath(data))
		return (sl_map_error("No path to resolve map"));
	return (0);
}
