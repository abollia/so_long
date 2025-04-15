/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:35:27 by abollia           #+#    #+#             */
/*   Updated: 2025/03/25 13:50:24 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	sl_file_check(char *map_file)
{
	size_t	i;
	size_t	len;
	size_t	dot;

	len = ft_strlen(map_file);
	i = 0;
	dot = 0;
	if (map_file[0] == ' ' || map_file[len - 1] == ' ')
		return (0);
	while (map_file[i])
	{
		if (map_file[i] == '.')
			dot++;
		i++;
	}
	if (dot != 1)
		return (0);
	if (ft_strncmp(&map_file[len - 4], ".ber", 4) != 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2 || !*av[1])
		sl_exit_handler("Error - Arguments", 1, NULL, NULL);
	if (!sl_file_check(av[1]))
		sl_exit_handler("Error - File", 1, NULL, NULL);
	sl_init_data(&data);
	sl_read_infile(av[1], &data);
	if (sl_map_check(&data))
		sl_exit_handler("Exiting - Invalid map", 1, NULL, &data);
	sl_init_player(&data);
	sl_display_init(&data);
	sl_display_map(&data);
	mlx_key_hook(data.mlx, sl_game_input, &data);
	mlx_close_hook(data.mlx, sl_game_close, &data);
	mlx_loop(data.mlx);
	ft_ffa(data.map.pattern);
	return (0);
}
