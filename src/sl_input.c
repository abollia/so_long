/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:32:07 by abollia           #+#    #+#             */
/*   Updated: 2025/03/19 13:53:13 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	sl_open_infile(char *infile, t_data *data)
{
	char	*file_path;

	file_path = ft_strjoin("maps/", infile);
	if (!file_path)
		sl_exit_handler("Error - Malloc (file_path)", 1, file_path, data);
	data->map.infile_fd = open(file_path, O_RDONLY);
	if (data->map.infile_fd < 0)
		sl_exit_handler("Error - Infile open failed", 0, file_path, data);
	free(file_path);
}

static void	sl_map_size(t_data *data)
{
	char	*line;

	line = get_next_line(data->map.infile_fd);
	while (line)
	{
		free(line);
		data->map.line_count++;
		line = get_next_line(data->map.infile_fd);
	}
	if (data->map.line_count == 0)
		sl_exit_handler("Error - Empty map", 1, NULL, data);
}

static void	sl_store_map(t_data *data)
{
	int		i;
	int		j;
	char	*line;

	data->map.pattern = malloc(sizeof(char *) * (data->map.line_count + 1));
	if (!data->map.pattern)
		sl_exit_handler("Error - Malloc (pattern global)", 1, NULL, data);
	i = 0;
	line = get_next_line(data->map.infile_fd);
	while (line)
	{
		data->map.pattern[i] = malloc(sizeof(char) * (strlen(line) + 1));
		if (!data->map.pattern[i])
			sl_exit_handler("Error - Malloc (pattern line)", 1, NULL, data);
		j = -1;
		while (line[++j])
			data->map.pattern[i][j] = line[j];
		data->map.pattern[i][j] = '\0';
		free(line);
		i++;
		line = get_next_line(data->map.infile_fd);
	}
	data->map.pattern[i] = NULL;
}

void	sl_read_infile(char *infile, t_data *data)
{
	sl_open_infile(infile, data);
	sl_map_size(data);
	close(data->map.infile_fd);
	data->map.infile_fd = -1;
	sl_open_infile(infile, data);
	sl_store_map(data);
	close(data->map.infile_fd);
	data->map.infile_fd = -1;
}
